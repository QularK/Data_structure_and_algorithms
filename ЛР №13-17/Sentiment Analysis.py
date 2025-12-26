import numpy as np
import pandas as pd
from sklearn.feature_extraction.text import TfidfVectorizer
from sklearn.model_selection import train_test_split
from sklearn.metrics import accuracy_score, precision_score, recall_score, f1_score, confusion_matrix
import matplotlib.pyplot as plt
import seaborn as sns
import re
import nltk
from nltk.corpus import stopwords
from nltk.stem import WordNetLemmatizer

# Загрузка необходимых ресурсов NLTK
nltk.download('stopwords')
nltk.download('wordnet')

class TextPreprocessor:
    """Класс для предобработки текста"""
    
    def init(self):
        self.stop_words = set(stopwords.words('english'))
        self.lemmatizer = WordNetLemmatizer()
    
    def preprocess_text(self, text):
        """Предобработка одного текста"""
        # Приведение к нижнему регистру
        text = text.lower()
        
        # Удаление HTML-тегов
        text = re.sub(r'<.*?>', '', text)
        
        # Удаление URL
        text = re.sub(r'http\S+|www\S+|https\S+', '', text)
        
        # Удаление специальных символов и цифр
        text = re.sub(r'[^a-zA-Z\s]', '', text)
        
        # Токенизация
        tokens = text.split()
        
        # Удаление стоп-слов и лемматизация
        tokens = [self.lemmatizer.lemmatize(word) for word in tokens 
                 if word not in self.stop_words and len(word) > 2]
        
        return ' '.join(tokens)

class SentimentClassifier:
    """Нейронная сеть для анализа тональности"""
    
    def init(self, input_dim, dropout_rate=0.5):
        """
        Инициализация нейронной сети
        
        Параметры:
        ----------
        input_dim : int, размерность входных признаков
        dropout_rate : float, вероятность отключения нейронов (0-1)
        """
        self.input_dim = input_dim
        self.dropout_rate = dropout_rate
        
        # Инициализация весов методом Xavier
        self.W1 = np.random.randn(input_dim, 64) * np.sqrt(1.0 / input_dim)
        self.b1 = np.zeros((1, 64))
        self.W2 = np.random.randn(64, 32) * np.sqrt(1.0 / 64)
        self.b2 = np.zeros((1, 32))
        self.W3 = np.random.randn(32, 2) * np.sqrt(1.0 / 32)
        self.b3 = np.zeros((1, 2))
        
        # История обучения
        self.loss_history = []
        self.accuracy_history = []
    
    def relu(self, x):
        """Функция активации ReLU"""
        return np.maximum(0, x)

  def relu_derivative(self, x):
        """Производная ReLU"""
        return (x > 0).astype(float)
    
    def softmax(self, x):
        """Функция активации Softmax"""
        exp_x = np.exp(x - np.max(x, axis=1, keepdims=True))
        return exp_x / np.sum(exp_x, axis=1, keepdims=True)
    
    def dropout(self, x, training=True):
        """
        Реализация Dropout
        
        Параметры:
        ----------
        x : numpy array, активации слоя
        training : bool, режим (True для обучения, False для инференса)
        """
        if not training:
            # В режиме инференса возвращаем все нейроны
            return x
        
        # Создаем маску для отключения нейронов
        mask = np.random.binomial(1, 1 - self.dropout_rate, size=x.shape) / (1 - self.dropout_rate)
        return x * mask
    
    def forward(self, X, training=True):
        """
        Прямое распространение через сеть
        
        Параметры:
        ----------
        X : numpy array, входные данные
        training : bool, режим обучения/инференса для Dropout
        """
        # Слой 1: 64 нейрона
        self.z1 = np.dot(X, self.W1) + self.b1
        self.a1 = self.relu(self.z1)
        self.a1 = self.dropout(self.a1, training)
        
        # Слой 2: 32 нейрона
        self.z2 = np.dot(self.a1, self.W2) + self.b2
        self.a2 = self.relu(self.z2)
        self.a2 = self.dropout(self.a2, training)
        
        # Выходной слой: 2 нейрона (положительный/отрицательный)
        self.z3 = np.dot(self.a2, self.W3) + self.b3
        self.a3 = self.softmax(self.z3)
        
        return self.a3
    
    def binary_cross_entropy(self, y_pred, y_true):
        """
        Вычисление Binary Cross-Entropy
        
        Параметры:
        ----------
        y_pred : numpy array, предсказания модели
        y_true : numpy array, истинные метки
        """

epsilon = 1e-8  # для избежания log(0)
        y_pred = np.clip(y_pred, epsilon, 1 - epsilon)
        loss = -np.mean(y_true * np.log(y_pred) + (1 - y_true) * np.log(1 - y_pred))
        return loss
    
    def backward(self, X, y, learning_rate):
        """
        Обратное распространение ошибки
        
        Параметры:
        ----------
        X : numpy array, входные данные
        y : numpy array, истинные метки
        learning_rate : float, скорость обучения
        """
        m = X.shape[0]
        
        # Ошибка выходного слоя
        delta3 = self.a3 - y
        
        # Градиенты для выходного слоя
        dW3 = np.dot(self.a2.T, delta3) / m
        db3 = np.sum(delta3, axis=0, keepdims=True) / m
        
        # Ошибка для второго скрытого слоя
        delta2 = np.dot(delta3, self.W3.T) * self.relu_derivative(self.a2)
        
        # Градиенты для второго скрытого слоя
        dW2 = np.dot(self.a1.T, delta2) / m
        db2 = np.sum(delta2, axis=0, keepdims=True) / m
        
        # Ошибка для первого скрытого слоя
        delta1 = np.dot(delta2, self.W2.T) * self.relu_derivative(self.a1)
        
        # Градиенты для первого скрытого слоя
        dW1 = np.dot(X.T, delta1) / m
        db1 = np.sum(delta1, axis=0, keepdims=True) / m
        
        # Обновление весов
        self.W3 -= learning_rate * dW3
        self.b3 -= learning_rate * db3
        self.W2 -= learning_rate * dW2
        self.b2 -= learning_rate * db2
        self.W1 -= learning_rate * dW1
        self.b1 -= learning_rate * db1
    
    def train(self, X_train, y_train, X_val, y_val, epochs=100, learning_rate=0.01, batch_size=32):
        """
        Обучение модели
        
        Параметры:
        ----------
        X_train, y_train : тренировочные данные и метки
        X_val, y_val : валидационные данные и метки
        epochs : int, количество эпох
        learning_rate : float, скорость обучения
        batch_size : int, размер мини-батча
        """
        n_samples = X_train.shape[0]
        
        for epoch in range(epochs):
            # Перемешивание данных
            indices = np.random.permutation(n_samples)
            X_shuffled = X_train[indices]
            y_shuffled = y_train[indices]
            
            epoch_loss = 0
            n_batches = 0
            
            # Обучение мини-батчами
            for i in range(0, n_samples, batch_size):
                X_batch = X_shuffled[i:i+batch_size]
                y_batch = y_shuffled[i:i+batch_size]
            # Прямое распространение (с Dropout)
                y_pred = self.forward(X_batch, training=True)
                
                # Вычисление потерь
                loss = self.binary_cross_entropy(y_pred, y_batch)
                epoch_loss += loss
                n_batches += 1
                
                # Обратное распространение
                self.backward(X_batch, y_batch, learning_rate)
            
            # Средние потери за эпоху
            avg_loss = epoch_loss / n_batches
            self.loss_history.append(avg_loss)
            
            # Оценка на валидационной выборке
            val_accuracy = self.evaluate(X_val, y_val)
            self.accuracy_history.append(val_accuracy)
            
            if (epoch + 1) % 10 == 0:
                print(f"Эпоха {epoch + 1}/{epochs}: Loss = {avg_loss:.4f}, Val Accuracy = {val_accuracy:.4f}")
    
    def predict(self, X):
        """
        Предсказание для новых данных (без Dropout)
        """
        # Прямое распространение без Dropout
        y_pred_proba = self.forward(X, training=False)
        # Возвращаем класс с максимальной вероятностью
        return np.argmax(y_pred_proba, axis=1)
    
    def predict_proba(self, X):
        """
        Возвращает вероятности классов
        """
        return self.forward(X, training=False)
    
    def evaluate(self, X, y):
        """
        Оценка точности модели
        """
        y_pred = self.predict(X)
        accuracy = accuracy_score(y, y_pred)
        return accuracy

def create_sample_dataset():
    """
    Создание примерного датасета с отзывами
    """
    positive_reviews = [
        "This movie was absolutely fantastic! I loved every minute of it.",
        "Great acting and an engaging storyline. Highly recommended.",
        "One of the best films I've seen this year. Outstanding performance.",
        "I really enjoyed this movie. The plot was interesting and well-developed.",
        "Excellent cinematography and great direction. A must-watch!",
        "Wonderful film with amazing characters. I was captivated from start to finish.",
        "Superb movie! The ending was perfect and satisfying.",
        "A masterpiece of modern cinema. Brilliant in every aspect.",
        "I loved the character development and the emotional depth.",
        "Fantastic movie, would definitely watch it again!"
    ]
    
    negative_reviews = [
        "Terrible movie. Waste of time and money.",
        "Poor acting and a boring plot. I couldn't finish it.",
        "One of the worst films I've ever seen. Avoid at all costs.",
        "Disappointing and predictable. Nothing original here.",
        "Awful cinematography and bad direction. Save your time.",
        "I hated this movie. The characters were poorly developed.",
        "Bad movie with a confusing storyline. Not recommended.",
        "A complete disaster. Nothing worked in
