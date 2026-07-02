

void RemmotControl(){
  
  //Security Control
  if(Remot_Change_Security == 1){
    Remot_Change_Security = 0;
    if(Remot_Security == 1){
      number = 1;
      Security_on();
    }
    
    if(Remot_Security == 0){
      number = 1;
      Security_off();
    }
    
  }
  
  //Rele Control
  if(Remot_Change_Rele == 1){
    Remot_Change_Rele = 0;
    if(Remot_Rele == 1){
      Rele1_on();
    }
    
    if(Remot_Rele == 0){
      Rele1_off();
    }
    
  }
  
  
  
}