/* Copyright 2019 The TensorFlow Authors. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
==============================================================================*/

#include <TensorFlowLite.h>

#include "main_functions.h"

#include "detection_responder.h"
#include "image_provider.h"
#include "model_settings.h"
#include "person_detect_model_data.h"
#include "tensorflow/lite/micro/micro_error_reporter.h"
#include "tensorflow/lite/micro/micro_interpreter.h"
#include "tensorflow/lite/micro/micro_mutable_op_resolver.h"
#include "tensorflow/lite/schema/schema_generated.h"
#include "tensorflow/lite/version.h"

#include <Keypad.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#define SERVO_PIN A1
#define LED_red A0
#define LED_blue A2
#define LED_green A3
#define Buzzer A6
Servo servo;
LiquidCrystal_I2C lcd(0x27, 16, 2);
int count=0;
int pos=0;
boolean correct=false;
volatile byte state=LOW;
unsigned long Time=0;
unsigned long detected=0;

char *password="1234";
const byte rows = 4;
const byte cols = 4;

char keys[rows][cols] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}};

byte rowPins[rows] = {10, 9, 8, 6};
byte colPins[cols] = {5, 4, 3, 2};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rows, cols);

// Globals, used for compatibility with Arduino-style sketches.
namespace {
tflite::ErrorReporter* error_reporter = nullptr;
const tflite::Model* model = nullptr;
tflite::MicroInterpreter* interpreter = nullptr;
TfLiteTensor* input = nullptr;

// In order to use optimized tensorflow lite kernels, a signed int8_t quantized
// model is preferred over the legacy unsigned model format. This means that
// throughout this project, input images must be converted from unisgned to
// signed format. The easiest and quickest way to convert from unsigned to
// signed 8-bit integers is to subtract 128 from the unsigned value to get a
// signed value.

// An area of memory to use for input, output, and intermediate arrays.
constexpr int kTensorArenaSize = 136 * 1024;
static uint8_t tensor_arena[kTensorArenaSize];
}  // namespace

// The name of this function is important for Arduino compatibility.
void setup() {
   pinMode(LED_red, OUTPUT);
   pinMode(LED_blue, OUTPUT);
   pinMode(LED_green, OUTPUT);
   pinMode(Buzzer, OUTPUT);  
   lcd.init();
   servo.attach(SERVO_PIN);
   servo.write(0);
   delay(1000);
   servo.detach();
   keypad.setDebounceTime(100);
  // Set up logging. Google style is to avoid globals or statics because of
  // lifetime uncertainty, but since this has a trivial destructor it's okay.
  // NOLINTNEXTLINE(runtime-global-variables)
  static tflite::MicroErrorReporter micro_error_reporter;
  error_reporter = &micro_error_reporter;

  // Map the model into a usable data structure. This doesn't involve any
  // copying or parsing, it's a very lightweight operation.
  model = tflite::GetModel(g_person_detect_model_data);
  if (model->version() != TFLITE_SCHEMA_VERSION) {
    TF_LITE_REPORT_ERROR(error_reporter,
                         "Model provided is schema version %d not equal "
                         "to supported version %d.",
                         model->version(), TFLITE_SCHEMA_VERSION);
    return;
  }

  // Pull in only the operation implementations we need.
  // This relies on a complete list of all the ops needed by this graph.
  // An easier approach is to just use the AllOpsResolver, but this will
  // incur some penalty in code space for op implementations that are not
  // needed by this graph.
  //
  // tflite::AllOpsResolver resolver;
  // NOLINTNEXTLINE(runtime-global-variables)
  static tflite::MicroMutableOpResolver<5> micro_op_resolver;
  micro_op_resolver.AddAveragePool2D();
  micro_op_resolver.AddConv2D();
  micro_op_resolver.AddDepthwiseConv2D();
  micro_op_resolver.AddReshape();
  micro_op_resolver.AddSoftmax();

  // Build an interpreter to run the model with.
  // NOLINTNEXTLINE(runtime-global-variables)
  static tflite::MicroInterpreter static_interpreter(
      model, micro_op_resolver, tensor_arena, kTensorArenaSize, error_reporter);
  interpreter = &static_interpreter;

  // Allocate memory from the tensor_arena for the model's tensors.
  TfLiteStatus allocate_status = interpreter->AllocateTensors();
  if (allocate_status != kTfLiteOk) {
    TF_LITE_REPORT_ERROR(error_reporter, "AllocateTensors() failed");
    return;
  }

  // Get information about the memory area to use for the model's input.
  input = interpreter->input(0);
}

// The name of this function is important for Arduino compatibility.
void loop() {
  // Get image from provider.
  if (kTfLiteOk != GetImage(error_reporter, kNumCols, kNumRows, kNumChannels,
                            input->data.int8)) {
    TF_LITE_REPORT_ERROR(error_reporter, "Image capture failed.");
  }

  // Run the model on this input and make sure it succeeds.
  if (kTfLiteOk != interpreter->Invoke()) {
    TF_LITE_REPORT_ERROR(error_reporter, "Invoke failed.");
  }

  TfLiteTensor* output = interpreter->output(0);

  // Process the inference results.
  int8_t person_score = output->data.uint8[kPersonIndex];
  int8_t no_person_score = output->data.uint8[kNotAPersonIndex];
  RespondToDetection(error_reporter, person_score, no_person_score);
  
  servo.attach(SERVO_PIN);
  if(person_score>no_person_score)
  {
    count++;
    digitalWrite(LED_red, LOW);
    digitalWrite(LED_blue, HIGH);
    digitalWrite(LED_green, LOW); // 사람이 감지되면 파란색 불이 들어오도록 함
    lcd.clear();
    lcd.print("Person Detected");
    lcd.setCursor(0,1);
    lcd.print("Enter PASSWORD");
  }
  else
  {
    lcd.clear();
    digitalWrite(LED_red, LOW);
    digitalWrite(LED_blue, LOW);
    digitalWrite(LED_green, LOW);
    count=0;
  }

 if(count > 5){
   tone(Buzzer, 990); // 경보 울림
   digitalWrite(LED_red, HIGH);
   digitalWrite(LED_blue, LOW);
   digitalWrite(LED_green, LOW); // 빨간 불이 들어오도록 함
   while(correct!=true){ 
     while(pos<4) // 4자리를 입력받으면 멈춤
     {
       char key=keypad.getKey(); // 키패드로부터 입력받음
       if((key >= '0' && key <= '9') || (key >= 'A' && key <='D')
        || (key == '*' || key == '#'))
        {
          if(key=='*')
          {
            pos=0;
            correct=false;
          } // '*' 버튼을 누르면 리셋. 비밀번호를 처음부터 다시 입력할 수 있도록 함
          else if(key==password[pos])
          {
            correct=true;
            pos++;
          } // 입력받은 버튼이 password[pos] 와 값이 같다면 pos 를 1 증가. 다음 입력을 password 의 다음 자리와 비교할 수 있도록 함
          else
          {
            pos++;
            correct=false;
          } // 입력받은 버튼이 리셋버튼이 아니고, password[pos] 와 일치하지 않는 경우 correct 를 false 로 바꾸어주고 다음 입력을 받을 수 있도록 함
        }
     }
     pos = 0;
     lcd.clear();
     if(correct==false)
     {
     lcd.setCursor(5,0);
     lcd.print("WARNING");
     } // 비밀번호 4자리를 입력하였으나 일치아지 않을 경우 lcd 패널에 경고문을 띄움
   }
    count=0;
    state = HIGH;
    correct=false; // 작업을 마치고 다시 비밀번호를 입력받기 위해 변수 초기화
    lcd.clear();
    lcd.print("Access Allowed"); // lcd 에 안내문 출력
    noTone(Buzzer); // 경보 해제
    digitalWrite(LED_red, LOW);
    digitalWrite(LED_blue, LOW);
    digitalWrite(LED_green, HIGH); // 문이 열릴 때엔 초록 불이 들어오도록 함
    servo.write(90); // 도어락 해제
    delay(5000);
    servo.write(0); // 일정 시간 후 다시 잠금
    delay(1000);
    servo.detach();
}
}
