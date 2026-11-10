# Структура

### 🔹Начну с памяти указатели и ссылки. Проинициализировал переменные бинарными маркерами. 
<details>
<summary>Смотреть</summary>
<img width="1010" height="1012" alt="Снимок экрана от 2026-11-08 18-44-31" src="https://github.com/user-attachments/assets/8b7a9137-37eb-4e09-8c62-e67fcdd99b40" />

</details> 

### 🔹Termux Вышел за пределы выделеной памяти. 
<details>
<summary>Смотреть</summary>
<img width="1200" height="1920" alt="1252" src="https://github.com/user-attachments/assets/5dfea414-5bbd-4569-beab-70bb49a82101" />

</details>

**🔹Termux Размер структуры**
<details>
<summary>Смотреть</summary>
<img width="1200" height="1920" alt="1253" src="https://github.com/user-attachments/assets/f783f448-a6a1-4fbd-8843-57c0f1df0853" />

</details>

Положил 14 байт компилятор выделил 16. Два байта пустоты. Для адресной арифметики это критично. Процессор arm Android. 

**🔹Termux ARM любит 32 разряда?** 
<details>
<summary>Смотреть</summary>
<img width="1200" height="1920" alt="1254" src="https://github.com/user-attachments/assets/5dee1dd2-935b-4c85-9144-c8153e9645ed" />

</details>

Теперь у меня 3 переменных положил 7 байт компилятор выделил 12 байт. 
