#include <Arduino.h>
#include <BluetoothA2DPSink.h>
#include <driver/i2s.h>
#include <M5Core2.h>
#include "myGraphic.h"

#define I2S_BCK_PIN  12  // Bit Clock (BCK)
#define I2S_WS_PIN   0  // Word Select (WS)
#define I2S_DOUT_PIN 2  // Data Output (DOUT)


BluetoothA2DPSink a2dp_sink;

//void Write_TouchEventStructures(Event& e);

Button volumeBar(30, 30+50*2+20*2, 250, 50, false, "volumeBar");


void volumeButtonEvent(Event& e) {
  int color =  BLUE;

  //Write_TouchEventStructures(e);

  Button& b = *e.button;

  lcd.fillRoundRect (b.x, b.y, b.w, b.h,3, BLUE);
  lcd.fillRoundRect(b.x, b.y, b.w, b.h,3, color);
  lcd.setCursor(30,30+50*2+20*2);

  if (e.to.x > b.x + b.w / 2) {
    a2dp_sink.set_volume(a2dp_sink.get_volume() + 5);
  }
  else if (e.to.x < b.x + b.w / 2) {
    a2dp_sink.set_volume(a2dp_sink.get_volume() - 5);
  }

}

void setup() {
  M5.begin();
  M5.Lcd.println("Bluetooth A2DP Speaker");
  M5.Axp.SetSpkEnable(true);

  i2s_pin_config_t pinConfig = {
    .bck_io_num = I2S_BCK_PIN,
    .ws_io_num = I2S_WS_PIN,
    .data_out_num = I2S_DOUT_PIN,
    .data_in_num = I2S_PIN_NO_CHANGE
  };

  a2dp_sink.set_pin_config(pinConfig);
  a2dp_sink.start("M5stack Speaker");

  lcd.init();
  lcd.setRotation(1);
  lcd.setBrightness(128);


  lcd.setTextSize(2);
  lcd.setTextColor(WHITE);
  lcd.setCursor(30, 30);
  lcd.write("Bluetooth A2DP Speaker");

  lcd.setTextSize(4);
  lcd.fillRoundRect ( 30, 30+50*2+20*2, 250, 50, 3, BLUE);
  lcd.setCursor(30,30+50*2+20*2);
  lcd.setTextColor(ORANGE,BLUE);
  lcd.write("Volume");

  volumeBar.addHandler(volumeButtonEvent, E_DBLTAP);
}

void loop() {
  lcd.setTextSize(4);

  if (M5.BtnA.wasPressed()) {
    a2dp_sink.previous();
  }
  if (M5.BtnB.wasPressed()) {
    if (a2dp_sink.get_audio_state() == ESP_A2D_AUDIO_STATE_STARTED) {
      a2dp_sink.pause();
      lcd.fillRect(30, 30+50, lcd.width() - 30, 50, BLACK);
      lcd.setCursor(30, 30+50);
      lcd.setTextColor(RED);
      lcd.println("Paused");
    }
    else {
      a2dp_sink.play();
      lcd.fillRect(30, 30+50, lcd.width() - 30, 50, BLACK);
      lcd.setCursor(30, 30+50);
      lcd.setTextColor(GREEN);
      lcd.println("Playing");
    }
  }
  if (M5.BtnC.wasPressed()) {
    a2dp_sink.next();
  }

  delay(5);
  M5.update();
}


