/************************************************
* @file    main.c 
* @author  APBashara
* @date    5/2025
* 
* @brief   Main Code to run Tasks and Setup Peripherals
***********************************************/

/* Includes -----------------------------------------------------------------*/
#include "main.h"

/* Global Variables ---------------------------------------------------------*/
uint8_t packetRecv;
uint8_t LoRaPacketBuf[128];
uint8_t LoRaPacketLen;
uint8_t usbTxBuf[USB_BUF_LEN];
uint8_t usbBufLen;

Telemetry telemetry;

/* Function Implementation --------------------------------------------------*/

int main(void) {
  HAL_Init(); // Used for USB
  SystemClock_Config(); // Sets to 48MHz using HSI48
  GPIO_Init();
  MX_USB_DEVICE_Init();

  while (1) {
    if (packetRecv) {
      Toggle_Pin(LED_GPIO, LED_PIN); // Toggle the LED pin
      packetRecv = 0;
      // Lora_Receive(LoRaPacketBuf, &LoRaPacketLen); // Receive LoRa packet
      uint8_t LoRaPacketID = LoRaPacketBuf[0]; // Get the packet ID

      switch(LoRaPacketID) {
        // Start at buffer index 1 to skip the ID byte
        case LORA_SUSPENSION_ID: {
          telemetry.Suspension_Packet = *(LoRa_Suspension_Packet*)LoRaPacketBuf[1];
          break;
        }

        case LORA_GPS_ID: {
          LoRa_GPS_Packet* gpsPacket = (LoRa_GPS_Packet*)LoRaPacketBuf[1];
          break;
        }

        case LORA_ENGINE_ID: {
          LoRa_Engine_Data_Packet* enginePacket = (LoRa_Engine_Data_Packet*)LoRaPacketBuf[1];
          break;
        }

        case LORA_BRAKES_ACCEL_ID: {
          LoRa_Brakes_Accel_Packet* brakesAccelPacket = (LoRa_Brakes_Accel_Packet*)LoRaPacketBuf[1];
          break;
        }

        case LORA_TEMPERATURE_ID: {
          LoRa_Temperature_Packet* tempPacket = (LoRa_Temperature_Packet*)LoRaPacketBuf[1];
          break;
        }

        default:
          usbBufLen = snprintf((char*)usbTxBuf, USB_BUF_LEN, "Error: Unknown Packet ID %02X\r\n", LoRaPacketID);
          CDC_Transmit_FS(usbTxBuf, usbBufLen);
          break;
      }

      // Transmit CSV formated data
      usbBufLen = snprintf((char*)usbTxBuf, USB_BUF_LEN, "%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d,\r\n",
        telemetry.Suspension_Packet.FrontPot, telemetry.Suspension_Packet.RearPot, telemetry.GPS_Packet.latGPS,
        telemetry.GPS_Packet.longGPS, telemetry.GPS_Packet.Speed, telemetry.Engine_Data_Packet.BrakePressure,
        telemetry.Engine_Data_Packet.ThrottleADC, telemetry.Engine_Data_Packet.Steering, telemetry.Engine_Data_Packet.RPM,
        telemetry.Engine_Data_Packet.ThrottlePosSensor, telemetry.Engine_Data_Packet.Lambda,
        telemetry.Brakes_Accel_Packet.OilPressure, telemetry.Brakes_Accel_Packet.FrontBrakeTemp,
        telemetry.Brakes_Accel_Packet.RearBrakeTemp, telemetry.Brakes_Accel_Packet.AccelX, telemetry.Brakes_Accel_Packet.AccelZ,
        telemetry.Brakes_Accel_Packet.AccelY, telemetry.Temperature_Packet.AirTemp, telemetry.Temperature_Packet.CoolTemp
      );
      CDC_Transmit_FS(usbTxBuf, usbBufLen); // Transmit over USB CDC
    }
  }
}

void Error_Handler(void) {
  __disable_irq();
  while (1);

}
