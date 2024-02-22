#include <Arduino.h>

const int sensorEsquerdoPin = 17;   // Pino do sensor esquerdo
const int sensorDireitoPin = 16;    // Pino do sensor direito
const int sensorMeio = 2;   // Pino do sensor esquerdo
const int sensorDireitoPin1 = 15;    // Pino do sensor direito
const int motorEsquerdoPino1 = 22;  // Pino IN1 do motor esquerdo
const int motorEsquerdoPino2 = 21;  // Pino IN2 do motor esquerdo
const int motorDireitoPino1 = 18;   // Pino IN3 do motor direito
const int motorDireitoPino2 = 19;   // Pino IN4 do motor direito
int deadlinedireita = 0; // Logica para ignorar deadlines
int deadlineesquerda = 0; // Logica para ignorar deadlines

void avancar() {
    digitalWrite(motorEsquerdoPino1, LOW);  // Inverter HIGH e LOW para inverter a direção
    digitalWrite(motorEsquerdoPino2, HIGH);
    digitalWrite(motorDireitoPino1, HIGH);   // Inverter HIGH e LOW para inverter a direção
    digitalWrite(motorDireitoPino2, LOW);
}

void girarEsquerda() {
    digitalWrite(motorEsquerdoPino1, LOW);
    digitalWrite(motorEsquerdoPino2, LOW);  // Inverter HIGH e LOW para inverter a direção
    digitalWrite(motorDireitoPino1, HIGH);   // Inverter HIGH e LOW para inverter a direção
    digitalWrite(motorDireitoPino2, LOW);
}

void girarDireita() {
    digitalWrite(motorEsquerdoPino1, LOW);  // Inverter HIGH e LOW para inverter a direção
    digitalWrite(motorEsquerdoPino2, HIGH);
    digitalWrite(motorDireitoPino1, LOW);
    digitalWrite(motorDireitoPino2, LOW);  // Inverter HIGH e LOW para inverter a direção
}

void parar() {
    digitalWrite(motorEsquerdoPino1, LOW);
    digitalWrite(motorEsquerdoPino2, LOW);
    digitalWrite(motorDireitoPino1, LOW);
    digitalWrite(motorDireitoPino2, LOW);
}

void setup() {
    pinMode(sensorEsquerdoPin, INPUT);
    pinMode(sensorDireitoPin, INPUT);
    pinMode(motorEsquerdoPino1, OUTPUT);
    pinMode(motorEsquerdoPino2, OUTPUT);
    pinMode(motorDireitoPino1, OUTPUT);
    pinMode(motorDireitoPino2, OUTPUT);
}

void loop() {
    int leituraSensorEsquerdo = digitalRead(sensorEsquerdoPin);
    int leituraSensorDireito = digitalRead(sensorDireitoPin);
    int leiturasensorMeio = digitalRead(sensorMeio);
    int leituraSensorDireito1 = digitalRead(sensorDireitoPin1);


    if ( leiturasensorMeio == HIGH ) {
        avancar();
        // Ambos os sensores estão na linha preta, siga em frente.
    }else if (leituraSensorEsquerdo == LOW && leituraSensorDireito == LOW && leiturasensorMeio == LOW ) {
        if(deadlinedireita == 1){
          girarEsquerda();
          delay(100);
          deadlinedireita == 0;

        }else if(deadlineesquerda == 1){
          girarDireita;
          delay(100);
          deadlinedireita == 0;

        }
        // Desvio para a esquerda (sobre o piso branco).
    }else if (leituraSensorEsquerdo == HIGH && leituraSensorDireito == LOW && leiturasensorMeio == LOW ) {
        // Desvio para a esquerda (sobre o piso branco).
        girarEsquerda();
        delay(100);
        deadlineesquerda++;

    }else if (leituraSensorEsquerdo == LOW && leituraSensorDireito == HIGH && leiturasensorMeio == LOW ) {
        // Desvio para a esquerda (sobre o piso branco).
        girarDireita();
        delay(100);
        deadlinedireita++;

    } else if (leituraSensorEsquerdo == LOW && leituraSensorDireito == HIGH) {
        // Desvio para a esquerda (sobre o piso branco).
        girarDireita();
    } else if (leituraSensorEsquerdo == HIGH && leituraSensorDireito == LOW) {
        // Desvio para a direita (sobre o piso branco).
        girarEsquerda();
    } else {
        // Nenhum dos sensores está na linha preta, pare o robô.
        parar();
    }
}
