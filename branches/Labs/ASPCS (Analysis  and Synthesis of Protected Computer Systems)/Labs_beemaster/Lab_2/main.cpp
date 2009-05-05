#include <string>
#include <vector>
#include <iostream>
#include <cassert>

////////////////////////////////////////////////////////////////////////////////

/* Функция шифрования
 * @param _message - текст, который необходимо зашифровать
 * @param _key     - секретный ключ - ширина таблицы шифрования */
std::string Encrypt(const std::string& _message, size_t _key);

/* Decrypt function
 * @param _message - зашифрованный текст
 * @param _key     - ширина таблицы шифрования 
 * @returns        - расшифрованный текст */
std::string Decrypt(const std::string& _message, size_t _key);

////////////////////////////////////////////////////////////////////////////////

int main()
{
	// Тестовая строка
    const std::string message = "This is SPAAAARTAAAAAAAA!!!!!!!!!!!!111";
	// Тестовый ключ
    const int key = 3;

	// Шифрование
    const std::string encryptedMessage = Encrypt(message, key);
	// Расшифрование
    const std::string decryptedMessage = Decrypt(encryptedMessage, key);

	// Проверка соответствия
	assert(decryptedMessage == message);

	// Вывод результатов
    std::cout << "Message: " << message << std::endl
		<< "Encrypted message: " << encryptedMessage << std::endl
		<< "Decrypted message: " << decryptedMessage << std::endl;

    return 0;
}

////////////////////////////////////////////////////////////////////////////////

std::string Encrypt(const std::string& _message, size_t _key)
{
	// Секретная таблица шифрования
    std::vector<std::string> table;

	// Горизонтально заполняем таблицу подстроками сообщения 
    for ( size_t begin = 0; begin < _message.length(); begin += _key )
        table.push_back( _message.substr(begin, _key) );

    std::string result;

	// Для каждого символа
    for (size_t i = 0; i < _key; ++i)
	{
		// В каждой подстроке
		std::vector<std::string>::const_iterator it = table.begin();
		// Считываем его вертикально
        for (; it != table.end(); ++it)
			if ( i < it->size() )
				result += (*it)[i];
	}

    return result;
}

////////////////////////////////////////////////////////////////////////////////

std::string Decrypt(const std::string& _message, size_t _key)
{
	// Секретная таблица шифрования
    std::vector<std::string> table(_message.length() / _key);
    
	// Первый символ в зашифрованном сообщении
    std::string::const_iterator messageIt = _message.begin();

	// Добавляем символы в каждую строку _key раз
	for (size_t i = 0; i < _key; ++i)
	{
		std::vector<std::string>::iterator tableIt = table.begin();
		// В каждую строку
		for (; tableIt != table.end(); ++tableIt)
		{
			// Если символы закончились - перестаем добавлять
			if ( messageIt == _message.end() )
				break;

			*tableIt += *messageIt;
			++messageIt;
		}
	}

    std::string result;
	std::vector<std::string>::const_iterator it = table.begin();

	// Считываем горизонтально подстроки из таблицы в результирующую строку
    for (; it != table.end(); ++it)
        result += *it;

    return result;
}

////////////////////////////////////////////////////////////////////////////////
