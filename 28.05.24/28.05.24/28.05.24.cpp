#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Item {
    string name;
    int quantity;
};

class MealStrategy {
public:
    virtual string prepareMeal(const vector<Item>& fridge) const = 0;
    virtual ~MealStrategy() = default;
};

bool hasItem(const vector<Item>& fridge, const string& item, int quantity) {
    for (const auto& i : fridge) {
        if (i.name == item && i.quantity >= quantity) {
            return true;
        }
    }
    return false;
}

class BreakfastStrategy : public MealStrategy {
public:
    string prepareMeal(const vector<Item>& fridge) const override {
        if (hasItem(fridge, "eggs", 2)) {
            return "Омлет с яйцами";
        }
        else if (hasItem(fridge, "bread", 1)) {
            return "Тосты с хлебом";
        }
        else {
            return "Завтрак невозможен - недостаточно ингредиентов";
        }
    }
};

class LunchStrategy : public MealStrategy {
public:
    string prepareMeal(const vector<Item>& fridge) const override {
        if (hasItem(fridge, "chicken", 1) && hasItem(fridge, "rice", 1)) {
            return "Курица с рисом";
        }
        else if (hasItem(fridge, "pasta", 1)) {
            return "Паста";
        }
        else {
            return "Обед невозможен - недостаточно ингредиентов";
        }
    }
};

class DinnerStrategy : public MealStrategy {
public:
    string prepareMeal(const vector<Item>& fridge) const override {
        if (hasItem(fridge, "beef", 1) && hasItem(fridge, "potatoes", 1)) {
            return "Говядина с картофелем";
        }
        else if (hasItem(fridge, "salad", 1)) {
            return "Салат";
        }
        else {
            return "Ужин невозможен - недостаточно ингредиентов";
        }
    }
};

class Fridge {
private:
    vector<Item> items;
public:
    Fridge(const vector<Item>& initialItems) : items(initialItems) {}

    const vector<Item>& getItems() const {
        return items;
    }
};

class MealContext {
private:
    MealStrategy* strategy;
public:
    void setStrategy(MealStrategy* newStrategy) {
        strategy = newStrategy;
    }

    string prepareMeal(const Fridge& fridge) const {
        if (strategy) {
            return strategy->prepareMeal(fridge.getItems());
        }
        return "Стратегия не установлена";
    }
};

int main() {
    setlocale(LC_ALL, "Russian");
    vector<Item> initialItems = {
        {"eggs", 2},
        {"bread", 1},
        {"chicken", 1},
        {"rice", 1},
        {"beef", 1},
        {"potatoes", 0},
        {"salad", 1}
    };

    Fridge fridge(initialItems);

    MealContext mealContext;
    BreakfastStrategy breakfastStrategy;
    LunchStrategy lunchStrategy;
    DinnerStrategy dinnerStrategy;

    string timeOfDay;
    cout << "Введите время суток (morning/day/evening): ";
    cin >> timeOfDay;

    if (timeOfDay == "morning") {
        mealContext.setStrategy(&breakfastStrategy);
    }
    else if (timeOfDay == "day") {
        mealContext.setStrategy(&lunchStrategy);
    }
    else if (timeOfDay == "evening") {
        mealContext.setStrategy(&dinnerStrategy);
    }
    else {
        cout << "Некорректное время суток\n";
        return 1;
    }

    cout << mealContext.prepareMeal(fridge) << "\n";

    return 0;
}
