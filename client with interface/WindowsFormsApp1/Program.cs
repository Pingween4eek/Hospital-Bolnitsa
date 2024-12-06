using System;
using System.Drawing; // Для работы с изображениями
using System.Text.RegularExpressions;
using System.Windows.Forms;

// класс для считывания hex-кодов
public class HexToColor
{

    public HexToColor()
    {
    }

    public static Color HexStringToColor(string hexColor)
    {
        string hc = ExtractHexDigits(hexColor);
        if (hc.Length != 6)
        {
            return Color.Empty;
        }
        string r = hc.Substring(0, 2);
        string g = hc.Substring(2, 2);
        string b = hc.Substring(4, 2);
        Color color = Color.Empty;
        try
        {
            int ri
               = Int32.Parse(r, System.Globalization.NumberStyles.HexNumber);
            int gi
               = Int32.Parse(g, System.Globalization.NumberStyles.HexNumber);
            int bi
               = Int32.Parse(b, System.Globalization.NumberStyles.HexNumber);
            color = Color.FromArgb(ri, gi, bi);
        }
        catch
        {
            return Color.Empty;
        }
        return color;
    }

    public static string ExtractHexDigits(string input)
    {
        Regex isHexDigit
           = new Regex("[abcdefABCDEF\\d]+", RegexOptions.Compiled);
        string newnum = "";
        foreach (char c in input)
        {
            if (isHexDigit.IsMatch(c.ToString()))
                newnum += c.ToString();
        }
        return newnum;
    }

}

namespace SimpleInterface
{
    public class MainForm : Form
    {
        private Button startButton;
        private Button exitButton;

        // кнопки на главном экране
        private Button patientActions;
        private Button timeActions;

        // кнопки работы с пациентами
        private Button createPatientList;
        private Button searchPatient;
        private Button addPatient;
        private Button deletePatient;
        private Button printPatients;
        private Button exitButton2;

        // название проги
        private Label name;

        public MainForm()
        {
            // Устанавливаем заголовок и размеры окна
            this.Text = "Пример интерфейса с изображением";
            this.Size = new System.Drawing.Size(1000, 600);
            this.MinimumSize = new System.Drawing.Size(1000, 600);
            this.MaximumSize = new System.Drawing.Size(1000, 600);

            startButton = new Button();
            startButton.Location = new System.Drawing.Point(350, 250);
            startButton.Width = 300;
            startButton.Height = 50;
            this.Controls.Add(startButton);
            startButton.Text = "START";
            startButton.Font = new Font("Comic sans", 25, FontStyle.Bold);
            startButton.Click += Start_Programm;
            //startButton.BackColor = System.Drawing.Color.Red;

            this.Resize += (sender, e) => CenterButton();

            try
            {
                startButton.BackgroundImage = Image.FromFile("C:/Users/Ivan/source/repos/WindowsFormsApp1/WindowsFormsApp1/picure.png"); // Путь к изображению
                startButton.BackgroundImageLayout = ImageLayout.Stretch; // Растянуть изображение по кнопке
            }
            catch (Exception ex)
            {
                startButton.BackColor = HexToColor.HexStringToColor("#ffd059");
            }

            // Заголовок HOSPITAL BOLNITSA
            name = new Label()
            {
                Text = "HOSPITAL BOLNITSA",
                Font = new Font("Castellar", 52, FontStyle.Bold), //шрифт
                ForeColor = HexToColor.HexStringToColor("#00ffb3"), //цвет текста
                BackColor = Color.Transparent, //прозрачный фон
                TextAlign = ContentAlignment.TopCenter, //выравниваем по центру
                Location = new Point(50, 50), //ставим в точке (50, 50)
                Size = new Size(900, 150), //рамзер
            };
            this.Controls.Add(name); //добавление на экран

            // кнопка выхода из проги
            exitButton = new Button()
            {
                Text = "Выход",
                Font = new Font("Castellar", 24, FontStyle.Bold),
                ForeColor = HexToColor.HexStringToColor("#2e2e2e"),
                BackColor = HexToColor.HexStringToColor("#c23838"),
                Location = new Point(385, 500),
                Size = new Size(200, 50),
            };
            exitButton.Click += Exit_Programm; // функция, закрывающая прогу
            this.Controls.Add(exitButton);

            // кнопка, возвращающая на экран выбора действия
            exitButton2 = new Button()
            {
                Text = "Назад",
                Font = new Font("Castellar", 24, FontStyle.Bold),
                ForeColor = HexToColor.HexStringToColor("#2e2e2e"),
                BackColor = HexToColor.HexStringToColor("#c23838"),
                Location = new Point(385, 500),
                Size = new Size(200, 50),
            };
            exitButton2.Click += Back; // функция, возвращающая на экран выбора действия

            // кнопка "Работа с пациентами"
            patientActions = new Button()
            {
                Text = "Работа с пациентами",
                Font = new Font("Castellar", 24, FontStyle.Bold),
                ForeColor = HexToColor.HexStringToColor("#2c29ff"),
                BackColor = HexToColor.HexStringToColor("#69a0c7"),
                Location = new Point(100, 250),
                Size = new Size(375, 50),
                TextAlign = ContentAlignment.MiddleCenter,
            };
            patientActions.Click += Patient_Actions; // функция, удаляющая элементы экрана "Выбор действия" и добавляющая элементы экрана "Работа с пациентами"

            // кнопка "Работа со временем"
            timeActions = new Button()
            {
                Text = "Промотать время",
                Font = new Font("Castellar", 24, FontStyle.Bold),
                ForeColor = HexToColor.HexStringToColor("#0a6925"),
                BackColor = HexToColor.HexStringToColor("#75e093"),
                Location = new Point(500, 250),
                Size = new Size(375, 50),
                TextAlign = ContentAlignment.MiddleCenter,
            };

            // кнопка "Создать список пациентов"
            createPatientList = new Button()
            {
                Text = "Создать список пациентов",
                Font = new Font("Castellar", 14, FontStyle.Bold),
                ForeColor = HexToColor.HexStringToColor("#ad7400"),
                BackColor = HexToColor.HexStringToColor("#fffa61"),
                Location = new Point(50, 200),
                Size = new Size(275, 50),
                TextAlign = ContentAlignment.MiddleCenter,
            };

            // кнопка "Поиск пациента"
            searchPatient = new Button()
            {
                Text = "Поиск пациента",
                Font = new Font("Castellar", 18, FontStyle.Bold),
                ForeColor = HexToColor.HexStringToColor("#7a0696"),
                BackColor = HexToColor.HexStringToColor("#e6a9f5"),
                Location = new Point(350, 200),
                Size = new Size(275, 50),
                TextAlign = ContentAlignment.MiddleCenter,
            };

            // кнопка "Добавить пациента"
            addPatient = new Button()
            {
                Text = "Добавить пациента",
                Font = new Font("Castellar", 18, FontStyle.Bold),
                ForeColor = HexToColor.HexStringToColor("#009118"),
                BackColor = HexToColor.HexStringToColor("#8aff9d"),
                Location = new Point(650, 200),
                Size = new Size(275, 50),
                TextAlign = ContentAlignment.MiddleCenter,
            };

            // кнопка "Удалить пациента"
            deletePatient = new Button()
            {
                Text = "Удалить пациента",
                Font = new Font("Castellar", 18, FontStyle.Bold),
                ForeColor = HexToColor.HexStringToColor("#945113"),
                BackColor = HexToColor.HexStringToColor("#edb47e"),
                Location = new Point(185, 275),
                Size = new Size(275, 50),
                TextAlign = ContentAlignment.MiddleCenter,
            };

            // кнопка "Вывести список пациентов"
            printPatients = new Button()
            {
                Text = "Показать список пациентов",
                Font = new Font("Castellar", 14, FontStyle.Bold),
                ForeColor = HexToColor.HexStringToColor("#0752a8"),
                BackColor = HexToColor.HexStringToColor("#8bb3e0"),
                Location = new Point(485, 275),
                Size = new Size(275, 50),
                TextAlign = ContentAlignment.MiddleCenter,
            };

            // Фоновое изображение
            try
            {
                this.BackgroundImage = Image.FromFile("C:/Users/Ivan/source/repos/WindowsFormsApp1/WindowsFormsApp1/picure.png"); // Путь к изображению
                this.BackgroundImageLayout = ImageLayout.Stretch; // Растягиваем изображение по форме
            }
            catch (Exception ex)
            {
                this.BackColor = HexToColor.HexStringToColor("#ffe299");
            }

        }

        // Выход из программы
        private void Exit_Programm(object sender, EventArgs e)
        {
            this.Close();
        }

        private void CenterButton()
        {
            // Вычисляем координаты для центрирования кнопки
            startButton.Location = new Point(
                (this.ClientSize.Width - startButton.Width) / 2, // Горизонтально
                (this.ClientSize.Height - startButton.Height) / 2 // Вертикально
            );
        }

        // Нажатие стартовой кнопки
        private void Start_Programm(object sender, EventArgs e)
        {
            this.Controls.Remove(startButton); // Удаляем стартовую кнопку

            this.Controls.Add(patientActions); // Добавляем кнопку "Работа с пациентами"
            this.Controls.Add(timeActions); // Добавляем кнопку "Работа со временем"
        }

        // Нажатие кнопки работы с пациентами
        private void Patient_Actions(object sender, EventArgs e)
        {
            this.Controls.Remove(exitButton); // Удаляем кнопку выхода из проги
            this.Controls.Remove(patientActions); // Удаляем кнопку "Работа с пациентами"
            this.Controls.Remove(timeActions); // Удаляем кнопку "Работа со временем"
             
            this.Controls.Add(exitButton2); // Добавляем кнопку "Назад"
            this.Controls.Add(createPatientList); // Добавляем кнопку "Создать список пациентов"
            this.Controls.Add(searchPatient); // Добавляем кнопку "Поиск пациента"
            this.Controls.Add(addPatient); // Добавляем кнопку "Добавить пациента"
            this.Controls.Add(deletePatient); // Добавляем кнопку "Удалить пациента"
            this.Controls.Add(printPatients); // Добавляем кнопку "Вывести список пациентов"
        }

        // Нажатие кнопки назад, тут мы возвращаем убранные и убираем добавленные кнопки в прошлой функции
        private void Back(object sender, EventArgs e)
        {
            this.Controls.Add(exitButton);
            this.Controls.Add(patientActions);
            this.Controls.Add(timeActions);

            this.Controls.Remove(exitButton2);
            this.Controls.Remove(createPatientList);
            this.Controls.Remove(searchPatient);
            this.Controls.Remove(addPatient);
            this.Controls.Remove(deletePatient);
            this.Controls.Remove(printPatients);
        }

        [STAThread]
        public static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            Application.Run(new MainForm());
        }
    }
}