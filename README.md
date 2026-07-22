# data7-can

🌐 [Read in English](#-english-version) | 🇷🇺 [Читать на русском](#-русская-версия)

---

## 🌐 English Version

A repository dedicated to studying the CAN bus using the C programming language. The project is currently in the stage of gathering a theoretical framework and initial design.

### 🛠 Environment & Stack
* **Linux / Android / Termux**
* **C, ASM**
* **Bits, logic, memory, neuron**
* **Multimeter: voltage, direction, and CAN bus resistance**
* **VK Engineer's Log:** [[CAN_j1939 — Software development in C](https://vk.ru/j1939)]

### 🔌 Devices
* **CANable 2.0 USB-CAN V2.0 Pro S**
* **OBD2 Scanner (SCANMATIK)**
* **Multimeter**

### 💻 Software
* **Wireshark / Radare2**
* **In-house utility development**

### 🎯 Core Concepts
* **CAN bus** — a digital network, acting as a virtual database.
* **Monitoring** — a discovery and search tool.
* **Telematics** — a client-server architecture.

### 🗺 Project Navigation
* 📂 **[Multimeter measurements](/multimeter)** — Multimeter data and parameters
* 📂 **[Masks and shifts](/mask-shift)** — Operations with bitmasks and offsets
* 📂 **[J1939 Decoder](/viz-j1939)** — Protocol decoding module
* 📂 **[J1939 Analyzer](/j1939-analiz)** — Advanced traffic analysis tool
* 📂 **[Tests sandbox](/tests)** — Test scripts and playground

---

## 🇷🇺 Русская Версия

Репозиторий для изучения CAN-шины (протокол SAE J1939) на языке C. Проект находится на стадии сбора теоретической базы и проектирования. Здесь разрабатываются консольные утилиты для парсингаи декодирования и реверс-инжиниринга <<живых>> дампов (HEX) и логов автомобильных сетей. Практический анализ ориентирован на работу с системами коммерческого транспорта.

- ЭБУ ДВС (Weichai, Yuchai)
- Тормозные системы ABS/EBS (WABCO)
- Подвеска ECAS (WABCO)
- Трансмиссия АКПП (VOITH, ALLISON, FAST GEAR) 

### 🛠 Окружение и стек
* **Linux / Android / Termux**
* **C, ASM**
* **Биты, логика, память, нейрон**
* **Мультиметр, напряжение, сопротивление CAN-шины**
* **Дневник инженера ВК:** [[CAN_j1939 — Разработка утилит на C](https://vk.ru/j1939)]

### 🔌 Устройства
* **CANable 2.0 USB-CAN V2.0 Pro S**
* **OBD2-сканер (SCANMATIK)**
* **Мультиметр**

### 💻 Софт
* **Wireshark / Radare2**
* **Разработка своих утилит**

### 🎯 Основные понятия
* **CAN-шина** — это цифровая сеть, виртуальная база данных.
* **Мониторинг** — это поисковик.
* **Телематика** — это клиент-сервер.

### 🗺 Навигация по проекту
* 📂 **[Замеры мультиметром](/multimeter)**
* 📂 **[Маски сдвиги](/mask-shift)**
* 📂 **[Декодер j1939](/viz-j1939)**
* 📂 **[Анализатор j1939](/j1939-analiz)**
* 📂 **[Песочница tests](/tests)**



