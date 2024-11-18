int W = 0, X = 0, Y = 0, Z = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Ingrese la operación en el formato 'NEMONICO x,y' (Ejemplo: SUM 1,2):");

  // Pines display
  //Lado Izquerdo
  pinMode(8, OUTPUT); //F.
  pinMode(9, OUTPUT); //E

  //Lado Derecho
  pinMode(12, OUTPUT); //B
  pinMode(13, OUTPUT); //C

  //En Medio
  pinMode(10, OUTPUT); //A
  pinMode(7, OUTPUT); //G
  pinMode(11, OUTPUT); //D
}

void loop() {
  if (Serial.available() > 0) {
    String input = Serial.readStringUntil('\n');
    input.trim();
    processInput(input);
  }
}

// Función para procesar la entrada y mostrar resultado
void processInput(String input) {
  int spaceIndex = input.indexOf(' ');
  int commaIndex = input.indexOf(',');

  if (spaceIndex > 0 && commaIndex > spaceIndex) {
    String command = input.substring(0, spaceIndex);
    int num1 = input.substring(spaceIndex + 1, commaIndex).toInt();
    int num2 = input.substring(commaIndex + 1).toInt();
    int result = 0;

    if (command == "SUM") {
      result = num1 + num2;
    } else if (command == "RES") {
      result = num1 - num2;
    } else if (command == "MUL") {
      result = num1 * num2;
    } else if (command == "DIV") {
      if (num2 != 0) {
        result = num1 / num2;
      } else {
        Serial.println("Error: División por cero");
        return;
      }
    } else {
      Serial.println("Error: Comando no reconocido");
      help();
      return;
    }

    Serial.print("Resultado: ");
    Serial.println(result);

    if (result >= 0 && result <= 15) { // Solo muestra números entre 0 y 15
      displayNumber(result);
    } else {
      Serial.println("Resultado fuera de rango para el display (0-15)");
    }
  } else {
    Serial.println("Error: Formato incorrecto");
    help();
  }
}

// Función para mostrar un número en el display de 7 segmentos
void displayNumber(int num) {
  // Apaga todos los segmentos antes de mostrar el número
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(10, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);

  // Muestra el número según el código binario
  switch (num) {
    case 0: digitalWrite(10, LOW); digitalWrite(12, LOW); digitalWrite(13, LOW); digitalWrite(9, LOW); digitalWrite(8, LOW); digitalWrite(11, LOW); break; 
    case 1: digitalWrite(12, LOW); digitalWrite(13, LOW); break; 
    case 2: digitalWrite(10, LOW); digitalWrite(12, LOW); digitalWrite(7, LOW); digitalWrite(9, LOW); digitalWrite(11, LOW); break; 
    case 3: digitalWrite(10, LOW); digitalWrite(12, LOW); digitalWrite(7, LOW); digitalWrite(13, LOW); digitalWrite(11, LOW); break; 
    case 4: digitalWrite(7, LOW); digitalWrite(12, LOW); digitalWrite(8, LOW); digitalWrite(13, LOW); break; 
    case 5: digitalWrite(10, LOW); digitalWrite(8, LOW); digitalWrite(7, LOW); digitalWrite(13, LOW); digitalWrite(11, LOW); break; 
    case 6: digitalWrite(10, LOW); digitalWrite(8, LOW); digitalWrite(7, LOW); digitalWrite(13, LOW); digitalWrite(9, LOW); digitalWrite(11, LOW); break; 
    case 7: digitalWrite(10, LOW); digitalWrite(12, LOW); digitalWrite(13, LOW); break; 
    case 8: digitalWrite(10, LOW); digitalWrite(12, LOW); digitalWrite(13, LOW); digitalWrite(9, LOW); digitalWrite(8, LOW); digitalWrite(11, LOW); digitalWrite(7, LOW); break;
    case 9: digitalWrite(10, LOW); digitalWrite(12, LOW); digitalWrite(13, LOW); digitalWrite(8, LOW); digitalWrite(7, LOW); digitalWrite(11, LOW); break;
    case 10: digitalWrite(7, LOW); digitalWrite(8, LOW); digitalWrite(9, LOW); digitalWrite(10, LOW); digitalWrite(12, LOW); digitalWrite(13, LOW); break;
    case 11: digitalWrite(8, LOW); digitalWrite(9, LOW); digitalWrite(7, LOW); digitalWrite(11, LOW); digitalWrite(13, LOW); break;
    case 12: digitalWrite(10, LOW); digitalWrite(8, LOW); digitalWrite(9, LOW); digitalWrite(11, LOW); break;
    case 13: digitalWrite(12, LOW); digitalWrite(7, LOW); digitalWrite(9, LOW); digitalWrite(11, LOW); digitalWrite(13, LOW); break;
    case 14: digitalWrite(7, LOW); digitalWrite(8, LOW); digitalWrite(9, LOW); digitalWrite(10, LOW); digitalWrite(11, LOW); break;
    case 15: digitalWrite(10, LOW); digitalWrite(8, LOW); digitalWrite(9, LOW); digitalWrite(7, LOW); break;
    default: break;
  }
}

void help(){
  Serial.println(" SUM x,y (Realiza Suma) \n RES x,y (Realiza Resta) \n MUL x,y (Reliza Multiplicación) \n DIV x,y (Realiza Division)");
}
