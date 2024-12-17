using System;
using FlaUI.Core;
using FlaUI.UIA3;
using FlaUI.Core.AutomationElements;
using FlaUI.Core.Tools;

class UITests
{
    static void Main()
    {
        // Запускаем приложение
        var appPath = @"C:\Users\kolga\Desktop\Hospital-Bolnitsa-main\client with interface\WindowsFormsApp1\bin\Release\WindowsFormsApp1.exe"; // Укажите путь к вашему .exe-файлу
        var app = FlaUI.Core.Application.Launch(appPath);

        using (var automation = new UIA3Automation())
        {
            var mainWindow = app.GetMainWindow(automation);

            // Тест: Нажать кнопку "START"
            var startButton = mainWindow.FindFirstDescendant(cf => cf.ByText("START"))?.AsButton();
            if (startButton == null)
            {
                Console.WriteLine("Кнопка 'START' не найдена!");
                return;
            }
            startButton.Invoke();

            Console.WriteLine("Кнопка 'START' нажата");

            // Тест: Нажать кнопку "Работа с пациентами"
            var patientActionsButton = mainWindow.FindFirstDescendant(cf => cf.ByText("Работа с пациентами"))?.AsButton();
            if (patientActionsButton == null)
            {
                Console.WriteLine("Кнопка 'Работа с пациентами' не найдена!");
                return;
            }
            patientActionsButton.Invoke();

            Console.WriteLine("Кнопка 'Работа с пациентами' нажата");

            //Тест: Нажать "Создать пациента"
            var createPatientButton = mainWindow.FindFirstDescendant(cf => cf.ByText("Создать список пациентов"))?.AsButton();
            if (createPatientButton == null)
            {
                Console.WriteLine("Кнопка 'Создать список пациентов' не найдена!");
                return;
            }
            createPatientButton.Invoke();

            Console.WriteLine("Кнопка 'Создать список пациентов' нажата");

            //vvod
            var countPat = mainWindow.FindFirstDescendant(cf => cf.ByAutomationId("createtextbox1"))?.AsTextBox();
            if (countPat == null)
            {
                Console.WriteLine("Поле 'createtextbox1' не найдено!");
                return;
            }
            countPat.Enter("1");

            // Тест: Нажать кнопку "Отправить"
            var sendcountButton = mainWindow.FindFirstDescendant(cf => cf.ByText("Отправить"))?.AsButton();
            if (sendcountButton == null)
            {
                Console.WriteLine("Кнопка 'Отправить' не найдена!");
                return;
            }
            sendcountButton.Invoke();

            Console.WriteLine("Кнопка 'Отправить' нажата");

            // Тест: Заполнить текстовые поля
            var idField = mainWindow.FindFirstDescendant(cf => cf.ByAutomationId("Id"))?.AsTextBox();
            if (idField == null)
            {
                Console.WriteLine("Поле 'Имя' не найдено!");
                return;
            }
            idField.Enter("1");

            var nameField = mainWindow.FindFirstDescendant(cf => cf.ByAutomationId("Name"))?.AsTextBox();
            if (nameField == null)
            {
                Console.WriteLine("Поле 'Имя' не найдено!");
                return;
            }
            nameField.Enter("vlad");

            var surnameField = mainWindow.FindFirstDescendant(cf => cf.ByAutomationId("Surname"))?.AsTextBox();
            if (surnameField == null)
            {
                Console.WriteLine("Поле 'Имя' не найдено!");
                return;
            }
            surnameField.Enter("vladov");


            var genderField = mainWindow.FindFirstDescendant(cf => cf.ByAutomationId("Gender"))?.AsTextBox();
            if (genderField == null)
            {
                Console.WriteLine("Поле 'Имя' не найдено!");
                return;
            }
            genderField.Enter("vlad");


            var ageField = mainWindow.FindFirstDescendant(cf => cf.ByAutomationId("Age"))?.AsTextBox();
            if (ageField == null)
            {
                Console.WriteLine("Поле 'Имя' не найдено!");
                return;
            }
            ageField.Enter("10");

            var diagnosisField = mainWindow.FindFirstDescendant(cf => cf.ByAutomationId("Diagnosis"))?.AsTextBox();
            if (diagnosisField == null)
            {
                Console.WriteLine("Поле 'Имя' не найдено!");
                return;
            }
            diagnosisField.Enter("vladik");


            var statusField = mainWindow.FindFirstDescendant(cf => cf.ByAutomationId("Status"))?.AsTextBox();
            if (statusField == null)
            {
                Console.WriteLine("Поле 'Имя' не найдено!");
                return;
            }
            statusField.Enter("boleet");


            var doctorField = mainWindow.FindFirstDescendant(cf => cf.ByAutomationId("Doctor"))?.AsTextBox();
            if (doctorField == null)
            {
                Console.WriteLine("Поле 'Имя' не найдено!");
                return;
            }
            doctorField.Enter("professor_vlad_geyskiy");


            var departmentField = mainWindow.FindFirstDescendant(cf => cf.ByAutomationId("Department"))?.AsTextBox();
            if (departmentField == null)
            {
                Console.WriteLine("Поле 'Имя' не найдено!");
                return;
            }
            departmentField.Enter("geyskoe");


            var daysField = mainWindow.FindFirstDescendant(cf => cf.ByAutomationId("Days"))?.AsTextBox();
            if (daysField == null)
            {
                Console.WriteLine("Поле 'Имя' не найдено!");
                return;
            }
            daysField.Enter("3");

            Console.WriteLine("Текстовые поля заполнены");

            // Тест: Нажать кнопку "Отправить"
            var sendButton = mainWindow.FindFirstDescendant(cf => cf.ByText("Отправить"))?.AsButton();
            if (sendButton == null)
            {
                Console.WriteLine("Кнопка 'Отправить' не найдена!");
                return;
            }
            sendButton.Invoke();

            Console.WriteLine("Кнопка 'Отправить' нажата");





            //// Тест: Нажать кнопку "Вывести пациента"
            var printPatientButton = mainWindow.FindFirstDescendant(cf => cf.ByText("Показать список пациентов"))?.AsButton();
            if (printPatientButton == null)
            {
                Console.WriteLine("Кнопка 'показать пациентов' не найдена!");
                return;
            }
            printPatientButton.Invoke();

            Console.WriteLine("Кнопка 'показать пациента' нажата");

            //// Тест: Заполнить текстовые поля
            //var nameField = mainWindow.FindFirstDescendant(cf => cf.ByAutomationId("enterTextName"))?.AsTextBox();
            //if (nameField == null)
            //{
            //    Console.WriteLine("Поле 'Имя' не найдено!");
            //    return;
            //}
            //nameField.Enter("Иван");

            //var surnameField = mainWindow.FindFirstDescendant(cf => cf.ByAutomationId("enterTextSurname"))?.AsTextBox();
            //if (surnameField == null)
            //{
            //    Console.WriteLine("Поле 'Фамилия' не найдено!");
            //    return;
            //}
            //surnameField.Enter("Иванов");

            //Console.WriteLine("Текстовые поля заполнены");

            
        }

        // Завершаем приложение
        //app.Close();
    }
}
