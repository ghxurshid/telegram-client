// TelegramClientExampleCPP.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string.h>
#include <memory.h>
#include <locale>

#include "TelegramClient.h"

uint32_t main()
{
    setlocale(LC_ALL, "Russian");

    uint32_t apiId = 22236638;
    ByteArray apiHash = CreateByteArray(32);
    apiHash.data = (uint8_t*)"fdf44e15f78621fe8d76caefac19761a";
    
    // Номер телефона пользователя
    ByteArray phoneNum = CreateByteArray(13);
    phoneNum.data = (uint8_t*)"+998998346521";

    // Создаем экземпляр Telegram клиента с заданным API ID и API Hash
    TelegramClient client = CreateTelegramClient(apiId, apiHash);
    // Устанавливаем соединение с Telegram сервером
    Connect(client, false);

    // Проверяем, авторизован ли пользователь
    bool isAuth = IsUserAuthorized(client);
  
    // Если пользователь не авторизован
    if (!isAuth)
    {
        printf("Файл авторизации не существует :(\n");
 
        // Отправляем запрос на отправку кода аутентификации на указанный номер телефона
        ByteArray hash = SendCodeRequest(client, phoneNum);
        printf("Введите код из SMS:\n");
        ByteArray code = CreateByteArray(6); 
        uint32_t ret = scanf_s((char*)code.data);

        // Пытаемся авторизовать пользователя с полученным кодом
        TLUser* user = MakeAuth(client, phoneNum, hash, code);

        if (user != nullptr)
        {
            printf("Пользователь %s авторизован\n", user->FirstName.data);
        } 
    }
    else
    {
        printf("Файл авторизации существует :)\n");
    }
     
    // Получаем список контактов пользователя
    TLContacts contacts = GetContacts(client);
    uint32_t contactCount = contacts.size;
    printf("У вас %i контактов\n", contactCount);    
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
