#include <locale>
#include "Core.h"
#include "TelegramClient.h"

void Start()
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
