#include <iostream>
#include <vector>
#include <algorithm>
#include <conio.h>

// Типы зданий, их всего 4 (Дом, гараж, сарай и баня)
enum buildsType
{
	house = 0,
	garage,
	barn,
	bathhouse
};

// Типы комнат. Т.к. на участке может быть несколько построек разных типов,
// то и помещения в них тоже могут быть разные
enum roomsType
{
	living = 0,	// Гостиная
	kitchen,	// Кухня
	bedroom,	// Спальня
	children,	// Детская
	bathroom,	// Ванная
	anteroom,	// Предбанник
	washing,	// Помывочное
	steam,		// Парная
	indefinite  // Тип для гаража и сарая.
};

// Структура КОМНАТА. Тип комнаты, площадь, на каком этаже и высота потолков.
struct room
{
	int apartType;
	double square;
};

// Структура Этаж. На этаже от 2 до 4 комнат. Берём по максимуму.
// Условимся, что высота этажа во всех комнатах одинаковая, в реалиях
// на мансардном или подвальном этаже высота комнат может быть разная.
struct level
{
	std::vector<room> apartment;
	int height;
};

// Структура ПОСТРОЙКА
struct building
{
	int buildType;
	bool oven;
	std::vector<level> floors;
};

// Структура УЧАСТОК. На участке может быть только 4 здания (Дом, баня, гараж, сарай)
struct area
{
	std::vector<building> construction;
};

// Функция преобразования типа здания в его название
std::string buildName(int buildType)
{
	std::string result;
	if (buildType == 0)
		result = "HOUSE";
	else if (buildType == 1)
		result = "GARAGE";
	else if (buildType == 2)
		result = "BARN";
	else if (buildType == 3)
		result = "BATHHOUSE";
	else
		result = "N/A";
	return result;
}

// Функция преобразования типа комнаты в её название
std::string roomName(int roomType)
{
	std::string result;
	if (roomType == 0)
		result = "LIVING";
	else if (roomType == 1)
		result = "KITCHEN";
	else if (roomType == 2)
		result = "BEDROOM";
	else if (roomType == 3)
		result = "CHILDREN";
	else if (roomType == 4)
		result = "BATHROOM";
	else if (roomType == 5)
		result = "ANTEROOM";
	else if (roomType == 6)
		result = "WASHING";
	else if (roomType == 7)
		result = "STEAM";
	else if (roomType == 8)
		result = "GARAGE/BARN";
	else
		result = "N/A";
	return result;
}

// Функция ввода данных, она же функция инициализации.
bool initialization(std::vector<area>& village, bool example)
{
	/* Посёлок Хулимсунт, Ханты - Мансийский автономный округ, Берёзовский район
		1346 человек, 17 многоквартирных домов, сколько земельных участков не известно.
		Будем считать равное населению 1346.
		Вводим вектор khulimsunt, который будет содержать участки.
		khulimsunt[0] - первый участок, khulimsunt[1] - второй участок и т.д.*/
	//std::vector<area> village;
	std::vector<room> rooms;
	std::vector<level> floors;
	std::vector<building> build;
	int areasNumber, buildsNumber, floorsNumber, buildType, roomsNumber, roomType, floorHeight;
	std::string answer;
	double roomSquare;
	bool success = false, oven = false;
	do
	{
		// Если надо заполнить состояние посёлка случайным образом, то examlpe = True
		if (!example)
		{
			std::cout << "Enter number of areas in village (1 - 1346): ";
			std::cin >> areasNumber;
			// Проверяем введённое количество участков, оно не может быть 0, отрицательным и больше 1346.
			// На самом деле, для проверки хватит 2 или 3.
			while (areasNumber < 1 || areasNumber > 1346)
			{
				std::cout << "Invalid number of areas. Repeat input, please.\n";
				std::cin >> areasNumber;
			}
		}
		else
			// Генерация количества участков в посёлке
			areasNumber = std::rand() % 10;
		for (int i = 0; i < areasNumber; ++i)
		{
			if (!example)
			{
				// Проверяем введённое количество построек на участке, оно не может быть 0, отрицательным и не более 4 построек.
				std::cout << "Enter number of builds into area " << i + 1 << " (1 - 4): ";
				std::cin >> buildsNumber;
				while (buildsNumber < 1 || buildsNumber > 4)
				{
					std::cout << "The building number is incorrect. Please repeat the input.\n";
					std::cin >> buildsNumber;
				}
			}
			else
				// Генерация количества зданий на участке
				buildsNumber = std::rand() % 4 + 1;
			for (int j = 0; j < buildsNumber; ++j)
			{
				if (!example)
				{
					std::cout << "Choice type of build " << j + 1 << '\n';
					std::cout << "0 - house\n1 - garage\n2 - barn\n3 - bathhouse.\nEnter type of builds: ";
					std::cin >> buildType;
					while (buildType < 0 || buildType > 3)
					{
						std::cout << "The type of buildings is incorrect. Repeat input, please.\n";
						std::cin >> buildType;
					}
				}
				else
					//Генерация типа постройки
					buildType = std::rand() % 4;
				// В ДОМЕ и БАНЕ может быть печка
				if (buildType == 0 || buildType == 3)
				{
					if (!example)
					{
						std::cout << "Is there an oven in this building (Y/N/Yes/No)? ";
						std::cin >> answer;
						std::transform(answer.begin(), answer.end(), answer.begin(), ::toupper);
						if (answer == "YES" || answer == "Y")
						{
							oven = true;
							std::cout << "The oven is present.\n";
						}
						else if (answer == "NO" || answer == "N")
						{
							oven = false;
							std::cout << "There is no oven.\n";
						}
						else
						{
							oven = false;
							std::cout << "There is no oven.\n";
						}
					}
					else
						// Генерация наличия печи
						oven = std::rand() % 2;
				}
				// Для гаража и сарая достаточно по одному этажу
				if (buildType == 1 || buildType == 2)
					floorsNumber = 1;
				else
				{
					if (!example)
					{
						// Проверяем количество этажей в постройке, оно должно быть в диапазоне от 1 до 3
						std::cout << "Enter number of floors into build (1-3): ";
						std::cin >> floorsNumber;
						while (floorsNumber < 1 || floorsNumber > 3)
						{
							std::cout << "Invalid number of floors. Repeat input, please.\n";
							std::cin >> floorsNumber;
						}
					}
					else
						floorsNumber = std::rand() % 3 + 1;
				}
				for (int k = 0; k < floorsNumber; ++k)
				{
					if (!example)
					{
						std::cout << "Enter height of the floor " << k + 1 << " (250 - 500 centimeters): ";
						std::cin >> floorHeight;
						// Проверяем высоту этажа, предположим, что высота не может быть меньше 2 м 50 см и больше 5 метров.
						while (floorHeight < 250 || floorHeight > 500)
						{
							std::cout << "Invalid height of floors. Repeat input, please.\n";
							std::cin >> floorHeight;
						}
					}
					else
						// Генерация высоты этажа
						floorHeight = std::rand() % 251 + 250;
					// Для гаража и сарая достаточно по одной комнате тип НЕОПРЕДЕЛЁННЫЙ.
					if (buildType == 1 || buildType == 2)
					{
						roomsNumber = 1;
						roomType = 8;
					}
					else
					{
						if (!example)
						{
							std::cout << "Enter number of rooms into floor (2 - 4): ";
							std::cin >> roomsNumber;
							while (roomsNumber < 2 || roomsNumber > 4)
							{
								std::cout << "Invalid number of rooms. Repeat input, please.\n";
								std::cin >> roomsNumber;
							}
						}
						else
							// Генерация количества комнат на этаже
							roomsNumber = std::rand() % 3 + 2;
					}
					// Проверяем количество комнат на этаже. По условию задачи их может быть две, три или четыре.
					// Для гаража и сарая количество комнат уже определено, а для дома и бани - нет.
					if (buildType == 0 || buildType == 3)
					{
						for (int l = 0; l < roomsNumber; ++l)
						{
							if(!example)
							{
								std::cout << "Choice type of room " << l + 1 << "\n0 - living\n1 - kitchen\n2 - bedroom\n" << \
									"3 - Children room\n4 - bathroom\n5 - anteroom\n" << \
									"6 - washing room\n7 - steam room\n8 - Indefinite\nEnter type of room: ";
								std::cin >> roomType;
								while (roomType < 0 || roomType > 8)
								{
									std::cout << "Invalid room type of room " << l + 1 << ". Repeat input, please.\n";
									std::cin >> roomType;
								}
								std::cout << "Enter square of room " << l + 1 << " (16 - 100 m2): ";
								std::cin >> roomSquare;
								while (roomSquare < 16 || roomSquare > 100)
								{
									std::cout << "Invalid square of rooms. Repeat input, please.\n";
									std::cin >> roomSquare;
								}
							}
							else
								// Генерация типа комнаты и её площадь
							{
								roomType = std::rand() % 9;
								roomSquare = std::rand() % 84 + 16;
							}
							success = true;
							// Добавить комнату в вектор.
							rooms.push_back({ roomType, roomSquare });
						}
					}
					else
					{
						if(!example)
						{
							std::cout << "Enter square of barn/garage (m2): ";
							std::cin >> roomSquare;
							// Проверяем введённую площадь комнат. Условимся, что площадь не может быть меньше 16 и больше 100 кв.м.
							while (roomSquare < 16 || roomSquare > 100)
							{
								std::cout << "Invalid square of rooms. Repeat input, please.\n";
								std::cin >> roomSquare;
							}
						}
						else
							// Генерация площади гаража / сарая
							roomSquare = std::rand() % 84 + 16;
						// Добавляем комнату в вектор комнат.
						success = true;
						rooms.push_back({ roomType, roomSquare });
					}
					floors.push_back({rooms, floorHeight});
					rooms.clear();
				}
				build.push_back({ buildType, oven, floors});
				floors.clear();
				oven = false;
			}
			village.push_back({build});
			build.clear();
		}
	} while (!success);
	return true;
}

// Функция отображения данных о посёлке.
void showVillage(std::string villageName, std::vector<area>& village)
{
	int countRooms, countFloors, countBuidings, countAreas;
	room rooms;
	level floors;
	building build;
	area region;
	double result = 0;
	// Определяем количество участков в посёлке
	countAreas = village.size();
	std::cout << std::string(60, '=') << '\n';
	if (countAreas > 0)
	{
		std::cout << "Village name: " << villageName << '\n';
		std::cout << "Number areas: " << countAreas << '\n';
		for (int i = 0; i < countAreas; ++i)
		{
			region = village[i];
			// Определяем количество сооружений на участке
			countBuidings = region.construction.size();
			std::cout << "\nArea number: " << i + 1 << '\n';
			for (int j = 0; j < countBuidings; ++j)
			{
				build = region.construction[j];
				// Определяем этажность здания
				countFloors = build.floors.size();
				std::cout << "\tType of construction: " << buildName(build.buildType) << '\n';
				// Если в здании есть печка, то выводим соответствующее сообщение.
				if (build.oven)
					std::cout << "\t\tRussian oven is present.\n";
				for (int k = 0; k < countFloors; ++k)
				{
					floors = build.floors[k];
					std::cout << "\t\tFloor number: " << k + 1 << '\n' << "\t\tHeight of floor: " << floors.height << '\n';
					// Определяем количество комнат на этаже
					countRooms = floors.apartment.size();
					for (int l = 0; l < countRooms; ++l)
					{
						rooms = floors.apartment[l];
						std::cout << "\t\t\tRoom number: " << l + 1 << '\n' << \
							"\t\t\t\tType of room: " << roomName(rooms.apartType) << '\n' << "\t\t\t\tSquare of room: " << rooms.square << '\n';
						result += rooms.square;
					}
				}
			}
			std::cout << std::string(60, '=') << '\n' << "Total square rooms: " << result << '\n';
			result = 0;
			std::cout << "Press any key ...";
			std::cin.ignore();
			std::cin.clear();
			while (!_kbhit());
		}
	}
	else
		std::cout << "No one lives in the village\n";
	//std::cout << std::string(60, '=') << '\n';
	//std::cout << "Press any key ...";
	//while (!_kbhit());
};

// Главная функция, главное меню управления посёлком
// Можно внести данные о посёлке или посмотреть информацию о посёлке.
int main()
{
	std::vector<area> village;
	std::string cmd, villageName;

	while(true)
	{
		std::cout << "This program can manage the village.\n\nSelect action, please: \n" <<\
				     "add - create village\n" <<\
			         "gen - generate example village\n" << \
                     "show - display info about village\n" <<\
			         "bye - exit from program)\n\n" << \
                     "Enter command : ";
		std::cin >> cmd;
		std::transform(cmd.begin(), cmd.end(), cmd.begin(), ::toupper);
		if (cmd == "ADD")
		{
			if (villageName.length() == 0)
			{
				std::cout << "Enter name of village: ";
				std::cin >> villageName;
			}
			initialization(village, false);
		}
		else if (cmd == "GEN")
			{
				if (villageName.length() == 0)
				{
					std::cout << "Enter name of village: ";
					std::cin >> villageName;
				}
				initialization(village, true);
			}
		else if (cmd == "SHOW")
			showVillage(villageName, village);
		else if (cmd == "BYE")
			return 0;
		else
			std::cout << "Unknown command, repeat.\n";
		std::cout << "Press any key ...";
		while (!_kbhit());
		std::cout << "\x1B[2J\x1B[H";
	}
}