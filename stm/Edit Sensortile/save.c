ENV_UPDATE_MUL_100MS

//Florian
      uint8_t data[20] = {'B','A','T','T','E','R','Y','7','8','%','A','B','C','D','E','F','G','H','I','J'};
      //sendDataTX use for debug
      sendDataTX(data, sizeof(data));
      BattPC_Update(soc);
    //Florian