#include <iostream>
#include <string>
#include <vector>
#include <locale>

using namespace std;

class UserSystem {
public:
    bool checkSubscription(const string& username) {
        cout << "Проверка подписки для '" << username << "'... Подписка активна." << endl;
        return true;
    }

    void getUserPreferences(const string& username) {
        cout << "Загружены рекомендации для '" << username << "'." << endl;
    }
};

class CatalogSystem {
public:
    bool findMovie(const string& title) {
        cout << "Поиск фильма '" << title << "'... Фильм найден." << endl;
        return true;
    }

    void getMovieInfo(const string& title) {
        cout << "Информация о фильме '" << title << "' загружена." << endl;
    }
};

class PaymentSystem {
public:
    bool processPayment(double amount, const string& paymentDetails) {
        cout << "Списание " << amount << " руб. через '" << paymentDetails << "'... Успешно." << endl;
        return true;
    }
};

class StreamingSystem {
public:
    void startStreaming(const string& title, const string& quality) {
        cout << "Запуск воспроизведения '" << title << "' в качестве " << quality << "." << endl;
    }

    void stopStreaming() {
        cout << "Воспроизведение остановлено." << endl;
    }
};

class RecommendationSystem {
public:
    void sendNotification(const string& username, const string& message) {
        cout << "Пользователю '" << username << "' отправлено: " << message << endl;
    }
};

class CinemaFacade {
private:
    UserSystem user;
    CatalogSystem catalog;
    PaymentSystem payment;
    StreamingSystem streaming;
    RecommendationSystem recommendation;

public:
    void watchMovie(const string& username, const string& title,
        const string& quality, const string& paymentDetails) {
        cout << "\nНачало просмотра" << endl;

        if (!user.checkSubscription(username)) {
            cout << "Ошибка: Подписка не активна!" << endl;
            return;
        }

        if (!catalog.findMovie(title)) {
            cout << "Ошибка: Фильм не найден!" << endl;
            return;
        }

        catalog.getMovieInfo(title);

        if (quality == "4K" || quality == "Premium") {
            if (!payment.processPayment(299.0, paymentDetails)) {
                cout << "Ошибка: Оплата не прошла!" << endl;
                return;
            }
        }

        user.getUserPreferences(username);

        streaming.startStreaming(title, quality);

        recommendation.sendNotification(username, "Начат просмотр '" + title + "'");

        cout << "Просмотр закончен" << endl;
    }

    void stopMovie() {
        cout << "\nОстановка просмотра" << endl;
        streaming.stopStreaming();
        cout << "Просмотр остановлен" << endl;
    }
};

int main() {
    setlocale(LC_ALL, "Russian");

    CinemaFacade cinema;

    cinema.watchMovie("grigorev_01", "Аватар", "HD", "Карта *4321");

    cinema.watchMovie("petro", "Дюна", "4K", "Карта *5678");

    return 0;
}