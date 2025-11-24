
int sensorPin = A0;
int buzzer = 8;
int ledPin1 = 4;  // vermelho
int ledPin2 = 7;  // amarelo
int ledPin3 = 5;  // verde
int motor = 2;

struct Node {
  int value;
  Node* next;
};

Node* head = NULL;   
int listSize = 0;    
const int MAX_SIZE = 5;

void addReading(int v) {
  Node* newNode = new Node;
  newNode->value = v;
  newNode->next = NULL;

  if (head == NULL) {
    head = newNode;
    listSize = 1;
    return;
  }

  
  Node* temp = head;
  while (temp->next != NULL) temp = temp->next;
  temp->next = newNode;
  listSize++;

  
  if (listSize > MAX_SIZE) {
    Node* old = head;
    head = head->next;
    delete old;
    listSize--;
  }
}


float getMedia() {
  if (head == NULL) return 0;

  Node* temp = head;
  long soma = 0;

  while (temp != NULL) {
    soma += temp->value;
    temp = temp->next;
  }

  return (float)soma / listSize;
}

void setup() {
  pinMode(buzzer, OUTPUT);
  pinMode(motor, OUTPUT);
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);

  Serial.begin(9600);
}

void loop() {

 
  int leitura = analogRead(sensorPin);
  addReading(leitura);

  float media = getMedia();

  float desvio = leitura - media;

  int mapLeitura = map(leitura, 0, 1023, 0, 100);

  Serial.print("Leitura: ");
  Serial.print(leitura);
  Serial.print(" | Media: ");
  Serial.print(media);
  Serial.print(" | Desvio: ");
  Serial.println(desvio);

  if (desvio > 40) {
    // Vermelho
    digitalWrite(motor, HIGH);
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
    tone(buzzer, 1000);

  } else if (desvio > 10) {
    // Amarelo
    digitalWrite(motor, LOW);
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin3, LOW);
    tone(buzzer, 1500);

  } else {
    // Verde
    digitalWrite(motor, LOW);
    digitalWrite(ledPin1, LOW);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, HIGH);
    noTone(buzzer);
  }

  delay(50);
}
