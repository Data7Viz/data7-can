# Структура C++

<details>
<summary><b>🔹Начну с памяти указатели и ссылки. Проинициализировал переменные бинарными маркерами</b></summary>
<img width="1010" height="1012" alt="Снимок экрана от 2026-11-08 18-44-31" src="https://github.com/user-attachments/assets/8b7a9137-37eb-4e09-8c62-e67fcdd99b40" />
</details> 

<details>
<summary><b>🔹Termux Вышел за пределы выделеной памяти</b></summary>
<img width="1200" height="1920" alt="1252" src="https://github.com/user-attachments/assets/5dfea414-5bbd-4569-beab-70bb49a82101" />
</details>

<details>
<summary><b>🔹Termux Размер структуры</b></summary>
<img width="1200" height="1920" alt="1253" src="https://github.com/user-attachments/assets/f783f448-a6a1-4fbd-8843-57c0f1df0853" />
  
Положил 14 байт компилятор выделил 16. Два байта пустоты . Для адресной арифметики это критично. Процессор arm Android. 
</details>

<details>
<summary><b>🔹Termux ARM любит 32 разряда?</b></summary>
<img width="1200" height="1920" alt="1254" src="https://github.com/user-attachments/assets/5dee1dd2-935b-4c85-9144-c8153e9645ed" />
  
Теперь у меня 3 переменных положил 7 байт компилятор выделил 12 байт.
</details> 

<details>
<summary><b>🔹Убираем padding логическим мышлением</b></summary>
<img width="661" height="1044" alt="Снимок экрана от 2026-11-10 19-20-24" src="https://github.com/user-attachments/assets/aa40b698-57e3-477a-9fc9-0f24f5f7bf0d" />
  
Сводим на минимум padding логическим мышлением на сколько это возможно. 1 байт в воздухе. 
</details>

<details>
<summary><b>🔹Адреса полей Padding в хвосте</b></summary>
 <img width="683" height="984" alt="Снимок экрана от 2026-11-10 20-39-39" src="https://github.com/user-attachments/assets/1e11b936-1b43-491e-a417-c13e6e220f44" />
 
Структуры так же как и массивы лежат в памяти последовательно. Тот байт который в воздухе в хвосте. Если uint8_t положить в средину поля паддинг будет по средине. Адрес должен быть кратен размеру данных голова адреса чётная хвост нечет. 
</details> 


<details>
<summary><b>🔹Указатели и адресная арифметика</b></summary>
<img width="675" height="933" alt="Снимок экрана от 2026-11-10 22-33-27" src="https://github.com/user-attachments/assets/9a670202-68f5-4bbc-b6ea-31f0f30e715a" />

Адрес это голова переменной. Голова в младших а хвост в старших адресах. Процессор начинает чтение с младших разрядов, а младшие разряды лежат в младших адресах.
Адреса перенёс на правую сторону биты с лева так логичней. В данном случае процессор склеил id + data и прочитал с младшего адреса (0x7f....54 это голова переменной id) поэтому переменная data оказалась в старших адресах. 
</details> 

<details>
<summary><b>🔹Указатель и две ссылки</b></summary>
<img width="1200" height="1920" alt="1261" src="https://github.com/user-attachments/assets/8bac5a04-a219-4a44-986f-4736228dfe34" />

</details>
