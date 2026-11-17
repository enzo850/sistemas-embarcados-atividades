
const int botaoAtivar = 3;
const int botaoDetectar = 2;
const int led = 9;
const int buzzer = 7;

enum Estado {
  DESATIVADO,
  ATIVADO,
  ALERTA
};

Estado estadoAtual = DESATIVADO;

bool ultimoAtivar = HIGH;
bool ultimoDetectar = HIGH;

void setup() {

  pinMode(botaoAtivar, INPUT_PULLUP);
  pinMode(botaoDetectar, INPUT_PULLUP);

  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);

  Serial.begin(9600);

  digitalWrite(led, LOW);
  noTone(buzzer);

  Serial.println("=== SISTEMA DE ALARME ===");
  Serial.println("Estado: DESATIVADO");
}

void loop() {

  bool ativar = digitalRead(botaoAtivar);
  bool detectar = digitalRead(botaoDetectar);

  // BOTAO DE ATIVACAO
  if (ativar == LOW && ultimoAtivar == HIGH) {

    delay(50);

    if (estadoAtual == DESATIVADO) {

      estadoAtual = ATIVADO;

      Serial.println("DESATIVADO -> ATIVADO");

    } else {

      estadoAtual = DESATIVADO;

      Serial.println("SISTEMA -> DESATIVADO");
    }
  }

  // BOTAO DE DETECCAO
  if (detectar == LOW &&
      ultimoDetectar == HIGH &&
      estadoAtual == ATIVADO) {

    delay(50);

    estadoAtual = ALERTA;

    Serial.println("ATIVADO -> ALERTA");
    Serial.println("INTRUSAO DETECTADA!");
  }

  // CONTROLE DO SISTEMA
  switch (estadoAtual) {

    case DESATIVADO:
      digitalWrite(led, LOW);
      noTone(buzzer);
      break;

    case ATIVADO:
      digitalWrite(led, HIGH);
      noTone(buzzer);
      break;

    case ALERTA:
      digitalWrite(led, HIGH);
      tone(buzzer, 1000);
      break;
  }

  ultimoAtivar = ativar;
  ultimoDetectar = detectar;
}
