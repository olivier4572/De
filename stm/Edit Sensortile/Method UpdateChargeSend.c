tBleStatus QuatPC_Update(SensorAxes_t *data)
{
  tBleStatus ret;

  uint8_t buff[2+ 6*SEND_N_QUATERNIONS];

  STORE_LE_16(buff  ,(HAL_GetTick()>>3));
#if SEND_N_QUATERNIONS == 1
  STORE_LE_16(buff+2,data[0].AXIS_X);
  STORE_LE_16(buff+4,data[0].AXIS_Y);
  STORE_LE_16(buff+6,data[0].AXIS_Z);
#elif SEND_N_QUATERNIONS == 2
  STORE_LE_16(buff+2,data[0].AXIS_X);
  STORE_LE_16(buff+4,data[0].AXIS_Y);
  STORE_LE_16(buff+6,data[0].AXIS_Z);

  STORE_LE_16(buff+8 ,data[1].AXIS_X);
  STORE_LE_16(buff+10,data[1].AXIS_Y);
  STORE_LE_16(buff+12,data[1].AXIS_Z);
#elif SEND_N_QUATERNIONS == 3
  STORE_LE_16(buff+2,data[0].AXIS_X);
  STORE_LE_16(buff+4,data[0].AXIS_Y);
  STORE_LE_16(buff+6,data[0].AXIS_Z);

  STORE_LE_16(buff+8 ,data[1].AXIS_X);
  STORE_LE_16(buff+10,data[1].AXIS_Y);
  STORE_LE_16(buff+12,data[1].AXIS_Z);

  STORE_LE_16(buff+14,data[2].AXIS_X);
  STORE_LE_16(buff+16,data[2].AXIS_Y);
  STORE_LE_16(buff+18,data[2].AXIS_Z);
#else
#error SEND_N_QUATERNIONS could be only 1,2,3
#endif
  ret = aci_gatt_update_char_value(sampleServHandle, QuaternionsPCCharHandle, 0, 2+6*SEND_N_QUATERNIONS, buff);

  if (ret != BLE_STATUS_SUCCESS){
    if(W2ST_CHECK_CONNECTION(W2ST_CONNECT_STD_ERR)){
      BytesToWrite =sprintf((char *)BufferToWrite, "Error Updating Quat Char\r\n");
      Stderr_Update(BufferToWrite,BytesToWrite);
    } else {
      ALLMEMS1_PRINTF("Error Updating Quat Char\r\n");
    }
    return BLE_STATUS_ERROR;
  }
  return BLE_STATUS_SUCCESS;
}