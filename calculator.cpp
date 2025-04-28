#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QGridLayout>
#include <QString>

class Calculator : public QWidget {
public:
    Calculator(QWidget *parent = nullptr);

private:
    QLineEdit *display;
    QString currentInput;
    void onButtonClicked();
    void onClear();
    void onEqual();
};

Calculator::Calculator(QWidget *parent)
    : QWidget(parent), currentInput("") {
    // تنظیمات نمایشگر
    display = new QLineEdit(this);
    display->setReadOnly(true);
    display->setAlignment(Qt::AlignRight);
    display->setFixedHeight(50);

    // دکمه‌ها
    QPushButton *buttons[4][4];
    const QString buttonLabels[4][4] = {
        {"7", "8", "9", "/"},
        {"4", "5", "6", "*"},
        {"1", "2", "3", "-"},
        {"0", ".", "=", "+"}
    };

    // چیدمان دکمه‌ها
    QGridLayout *layout = new QGridLayout;
    layout->addWidget(display, 0, 0, 1, 4);
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            buttons[i][j] = new QPushButton(buttonLabels[i][j], this);
            layout->addWidget(buttons[i][j], i + 1, j);
            connect(buttons[i][j], &QPushButton::clicked, this, &Calculator::onButtonClicked);
        }
    }

    // دکمه پاک کردن
    QPushButton *clearButton = new QPushButton("C", this);
    layout->addWidget(clearButton, 5, 0, 1, 4);
    connect(clearButton, &QPushButton::clicked, this, &Calculator::onClear);

    // تنظیمات نهایی پنجره
    setLayout(layout);
    setWindowTitle("ماشین حساب");
    setFixedSize(250, 300);
}

void Calculator::onButtonClicked() {
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button) return;
    
    QString buttonText = button->text();
    if (buttonText == "=") {
        onEqual();
    } else {
        currentInput += buttonText;
        display->setText(currentInput);
    }
}

void Calculator::onClear() {
    currentInput = "";
    display->clear();
}

void Calculator::onEqual() {
    // اجرای عملیات محاسباتی
    QString result;
    try {
        result = QString::number(currentInput.toDouble());
    } catch (...) {
        result = "Error";
    }
    display->setText(result);
    currentInput = "";
}

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    
    Calculator calculator;
    calculator.show();
    
    return app.exec();
}
