# Инструкция по сборке и запуску проекта

## Здесь находятся объединённые Level6, Level7, Level8

## 1. Сборка и запуск без Docker

### 📌 Установка зависимостей

При отсутствии указанных утилит выполните команду:
```sh
sudo apt update && sudo apt install -y build-essential cmake g++
```

### 🛠 Сборка проекта
```sh
mkdir -p build && cd build
cmake ..
make
```

### 🚀 Запуск сервера
```sh
./server
```

### 🚀 Запуск клиента
```sh
./client
```

---

## 2. Сборка и запуск с использованием Docker (CLI)

### 🏗 Сборка Docker-образа
```sh
docker build -t clientserver-docker .
```

### ▶ Запуск контейнера
```sh
docker run --rm -it -p 8080:8080 clientserver-docker
```

### 🔧 Сборка и запуск внутри контейнера
```sh
mkdir -p build && cd build
cmake ..
make
```

### 🚀 Запуск сервера
```sh
./server
```

### 🚀 Запуск клиента
```sh
./client
```

---

## 3. Сборка и запуск в Dev Container (VS Code)

### 🎯 Подготовка
1. Убедитесь, что у вас установлен **Docker** и **VS Code** с расширением **Remote - Containers**.
2. Откройте проект в **VS Code**.
3. Откройте командную палитру (**Ctrl+Shift+P**) и выберите **"Reopen in Container"**.

### 🔄 Сборка и запуск
```sh
mkdir -p build && cd build
cmake ..
make
```

### 🚀 Запуск сервера
```sh
./server
```

### 🚀 Запуск клиента
```sh
./client
```

Теперь сервер запущен и доступен по порту **8080**.

