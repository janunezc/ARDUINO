void setup() {
  // put your setup code here, to run once:

}

void loop() {
  Serial.println("Cycle");
  system ( "node ~/nodejs_projects/marie/pvcloud_api.js action='add_value' value='REAL TEST' value_type='ANY_TYPE_IS_FINE' value_label='ANY LABEL WORKS' captured_datetime='2000-01-01+10:23'");
  delay(1000);
  
}
