#include <Wire.h>
#include <LiquidCrystal_I2C.h>

const int addr = 0x27;
LiquidCrystal_I2C lcd(addr, 16, 2);

int pulsadorBanda = 7;
int pulsadorMoldes = 8;
int pulsadorRelleno = 9;
int pulsadorRegresar = 10;

int valorMotorBanda = 0;
int valorMotorMoldes = 0;
int valorMotorRelleno = 0;

const int releBanda = 2;
const int releMoldes = 3;
const int releRelleno = 5;

int opcionSeleccionada = 1;

void setup() {
  Wire.begin();
  lcd.begin(16, 2);
  lcd.print("Control Maquina");
  lcd.setCursor(0, 1);
  lcd.print("Empanadas");
  delay(2000);
  lcd.clear();

  pinMode(pulsadorBanda, INPUT);
  pinMode(pulsadorMoldes, INPUT);
  pinMode(pulsadorRelleno, INPUT);
  pinMode(pulsadorRegresar, INPUT);

  pinMode(releBanda, OUTPUT);
  pinMode(releMoldes, OUTPUT);
  pinMode(releRelleno, OUTPUT);

  digitalWrite(releBanda, LOW);
  digitalWrite(releMoldes, LOW);
  digitalWrite(releRelleno, LOW);
}

void loop() {
  while (true) {
    MENU();

    int pulsador = obtenerPulsadorPresionado();
    if (pulsador != 0) {
      delay(200);

      switch (opcionSeleccionada) {
        case 1:
          valorMotorBanda = !valorMotorBanda;
          actualizarEstadoMotor("Motor Banda", valorMotorBanda, releBanda);
          break;
        case 2:
          valorMotorMoldes = !valorMotorMoldes;
          actualizarEstadoMotor("Motor Moldes", valorMotorMoldes, releMoldes);
          break;
        case 3:
          valorMotorRelleno = !valorMotorRelleno;
          actualizarEstadoMotor("Motor Relleno", valorMotorRelleno, releRelleno);
          break;
        case 4:
          apagarTodo();
          return;
      }
    }
  }
}

int obtenerPulsadorPresionado() {
  for (int i = 1; i <= 4; ++i) {
    if (digitalRead(i + 5) == HIGH) {
      opcionSeleccionada = i;
      return i;
    }
  }
  return 0;
}
void MENU() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1.Banda");
  lcd.setCursor(8, 0);
  lcd.print("2.Moldes");
  lcd.setCursor(0, 1);
  lcd.print("3.Relleno");
  lcd.setCursor(8, 1);
  lcd.print("4.volver");
  delay(1000);
}

void actualizarEstadoMotor(const char *nombreMotor, int &valorTemporal, int pinActivador) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(nombreMotor);
  lcd.setCursor(0, 1);
  lcd.print(valorTemporal ? "Encendido" : "Apagado");

  digitalWrite(pinActivador, valorTemporal);
  delay(500);  // Breve espera para mejorar la legibilidad
}

void apagarTodo() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Apagando Todo");

  digitalWrite(releBanda, LOW);
  digitalWrite(releMoldes, LOW);
  digitalWrite(releRelleno, LOW);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Arduino Apagado");
  delay(2000);  // Espera antes de salir del programa
}
