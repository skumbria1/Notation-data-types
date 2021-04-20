#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <cmath>
#include <iomanip>
using namespace std;

void emptystr() {
	for (int i = 0; i < 4; i++) {
		cout << "                                                                ";
	}
}

void gotoxy(int x, int y) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;
	position.X = x;
	position.Y = y;
	SetConsoleCursorPosition(handle, position);
}

void setcolour(int x, int y, int z, WORD colour) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position;
	position.X = x;
	position.Y = y;
	DWORD cWritten;
	FillConsoleOutputAttribute(handle, colour, z, position, &cWritten);
}

int returnnum (char symbol, char* alphabet) {
	for (int i = 0; i < 62; i++) {
		if (symbol == alphabet[i]) {
			return i;
		}
	}
	return -1;
}

union uniint
{
	int num;
	int numInt;
} ;

union unifloat
{
	float num;
	unsigned int numInt;
} ;

union unidouble
{
	double num;
	unsigned long long numInt;
} ;

void charout() {
	const int space = 32;
	const int backspace = 8;
	const int escape = 27;
	const int enter = 13;
	const int keyRight = 77;
	const int keyLeft = 75;
	const int keyUp = 72;
	const int keyDown = 80;
	const int tab = 9;
	system("cls");
	char symbol;
	cout << "Введите символ ";
	symbol = _getch();
	cout << endl;
	cout << "Код символа: ";
	cout << (int)symbol;
	if (symbol == 'а') {
		symbol = _getch();
		cout << " " << (int)symbol;
	}
	cout << endl;
	cout << "В двоичной системе счисления: ";
	for (int z = sizeof(char) - 1; z >= 0; z--)
	{
		for (int i = 128; i > 0; i >>= 1)
		{
			if (i & symbol)
			{
				cout << "1";
			}
			else
			{
				cout << "0";
			}
		}
	}
	cout << endl;
	switch (symbol) {
	case enter: cout << "enter"; break;
	case escape: cout << "escape"; break;
	case keyRight: cout << "right key"; break;
	case keyLeft: cout << "left key"; break;
	case keyUp: cout << "up key"; break;
	case keyDown: cout << "down key"; break;
	case backspace: cout << "backspace"; break;
	case space: cout << "space"; break;
	case tab: cout << "tab"; break;
	default: {
		cout << symbol;
	}
	}
	cout << endl;
	system("pause");
}

void stringHandler (int numSys, char ent[100], int &startIndex, bool dot, char* alphabet) {
	const int space = 32;
	const int backspace = 8;
	const int escape = 27;
	const int enter = 13;
	bool T = 1;
	char buffer;
	int	index = 0;

	while (T) {
		buffer = _getch();
		switch (buffer) {
		case enter: T = 0; break;
		case escape: exit(0); break;
		case backspace: {
			if (index > 0) {
				cout << "\b \b";
				ent[index - 1] = 0;
				index--;
			}
			break;
		}
		case '-': {
			if (index == 0) {
				ent[index] = '-';
				cout << '-';
				index++;
			}
			break;
		}
		case '.': {
			if (dot) {
				if (index == 0) break;
				bool dotHere = 0;
				for (int i = 0; i < 99; ) {// < 32
					if (ent[i] == '.') { dotHere = 1; break; }
					_asm {
						mov eax, i
						inc i
					}
				}
				if (dotHere) break;
				if (ent[0] == '-' and index == 1) break;
				cout << '.';
				ent[index] = '.';
				index++;
			}
			break;
		}
		default: {
			if (index == 99) break; //==31
			for (int i = 0; i < numSys; i++) {
				if (buffer == alphabet[i]) {
					cout << alphabet[i];
					ent[index] = buffer;
					index++;
					break;
				}
			}
		}
		}
	}
	startIndex = index;
	if (startIndex < 100) startIndex--; //было < 32
}

uniint intHandling10(int numSys, char ent[100], int startIndex, char* alphabet) {
	uniint number;
	number.num = 0;
	bool isNegative = 0;
	int power = 0;

	for (int i = startIndex; i > -1; i--) {
		if (ent[i] == '-') {
			isNegative = 1;
			break;
		}
		number.num += returnnum(ent[i], alphabet) * pow(numSys, power);
		power++;
	}
	if (isNegative) number.num *= (-1);
	return number;
}

unifloat floatHandling10(int numSys, char ent[100], int startIndex, char* alphabet) {
	int dotIndex = startIndex, powerpos = 0, powerneg = -1;
	unifloat number;
	number.num = 0;
	bool isNegative = 0;

	for (int i = 0; i < 99; i++) {
		if (ent[i] == '.') dotIndex = i;
	}
	powerneg *= startIndex - dotIndex;
	for (int i = dotIndex; i > -1; i--) {
		if (ent[i] == '.') continue;
		if (ent[i] == '-') {
			isNegative = 1;
			break;
		}
		number.num += returnnum(ent[i], alphabet) * pow(numSys, powerpos);
		powerpos++;
	}
	if (dotIndex != startIndex) {
		for (int i = startIndex; i > dotIndex; i--) {
			number.num += returnnum(ent[i], alphabet) * pow(numSys, powerneg);
			powerneg++;
		}
	}
	if (isNegative) number.num *= (-1);

	return number;
}

unidouble doubleHandling10(int numSys, char ent[100], int startIndex, char* alphabet) {
	int dotIndex = startIndex, powerpos = 0, powerneg = -1;
	unidouble number;
	number.num = 0;
	bool isNegative = 0;

	for (int i = 0; i < 99; i++) {
		if (ent[i] == '.') dotIndex = i;
	}
	powerneg *= startIndex - dotIndex;
	for (int i = dotIndex; i > -1; i--) {
		if (ent[i] == '.') continue;
		if (ent[i] == '-') {
			isNegative = 1;
			break;
		}
		number.num += returnnum(ent[i], alphabet) * pow(numSys, powerpos);
		powerpos++;
	}
	if (dotIndex != startIndex) {
		for (int i = startIndex; i > dotIndex; i--) {
			number.num += returnnum(ent[i], alphabet) * pow(numSys, powerneg);
			powerneg++;
		}
	}
	if (isNegative) number.num *= (-1);

	return number;
}

template<typename T>
void handling2(T uninum) {
	unsigned int intMax = 2147483648;
	unsigned long long longIntMax = 9223372036854775808;
	if (sizeof(uninum.num) * 8 == 32) {
		for (unsigned int i = intMax; i > 0; i >>= 1)
		{
			if (i & uninum.numInt)
			{
				cout << "1";
			}
			else
			{
				cout << "0";
			}
		}
	}
	else {
		for (unsigned long long i = longIntMax; i > 0; i >>= 1)
		{
			if (i & uninum.numInt)
			{
				cout << "1";
			}
			else
			{
				cout << "0";
			}
		}
	}
}

template <typename T>
void Shift(T uninum, int dataType) {
	const int escape = 27;
	const int enter = 13;
	const int keyLeft = 75;
	const int keyRight = 77;
	int from = 0, to, n, size = 2;
	bool ex = 1, dir;
	char ch;
	while (ex) {
		gotoxy(0, 22);
		cout << "Номер младшего бита: < " << from << " >" << "\n\n";
		switch (ch = _getch()) {
		case keyRight: { 
			if (from > 0) {
				from--;
			}
			break; 
		}
		case keyLeft: { 
			if ((dataType == 2) or (dataType == 3)) { //4 байта
				if (from < 30) {
					from++;
				}
			}
			else {
				if (from < 62) {
					from++;
				}
			}
			break; 
		}
		case enter: ex = 0; break;
		case escape: exit(0); break;
		default: break;
		}
	}
	ex = 1;
	while (ex) {
		gotoxy(0, 24);
		cout << "Размер группы бит: < " << size << " >" << "\n\n";
		switch (ch = _getch()) {
		case keyRight: {
			if (size > 2) {
				size--;
			}
			break;
		}
		case keyLeft: {
			if ((dataType == 2) or (dataType == 3)) { //4 байта
				if (size < (32 - from)) {
					size++;
				}
			}
			else { //8 байт
				if (size < (64 - from)) {
					size++;
				}
			}
			break;
		}
		case enter: ex = 0; break;
		case escape: exit(0); break;
		default: break;
		}
	}
	while (true) {
		cout << "На сколько сдвинуть: ";
		cin >> n;
		if (n < 1) {
			gotoxy(0, 26);
			continue;
		}
		else { break; }
	}
	cout << "\n\n";
	ex = 1;
	while (ex) {
		gotoxy(0, 28);
		cout << "Влево - 1, вправо - 0" << "\n\n";
		switch (ch = _getch()) {
		case '1': dir = 1; ex = 0;  break;
		case '0': dir = 0; ex = 0;  break;
		case escape: exit(0); break;
		default: break;
		}
	}
	to = size + from - 1;
	n = n % size;
	T a = uninum, b, b1, b2;
	b.numInt = 0;
	for (int i = from; i <= to; i++) {
		b.numInt += a.numInt & (1ui64 << i);
	}
	a.numInt -= b.numInt;
	if (dir) { //влево
		b1.numInt = b.numInt << n;
		b2.numInt = b.numInt >> ((to - from) + 1 - n);
	}
	else {
		b1.numInt = b.numInt << ((to - from) + 1 - n);
		b2.numInt = b.numInt >> n;
	}
	b.numInt = 0;
	for (int i = from; i <= to; i++) {
		b.numInt += (b1.numInt | b2.numInt) & (1ui64 << i);
	}
	a.numInt = (a.numInt | b.numInt);
	cout << "В двоичной системе: ";
	handling2(a);
	cout << "\n\nВ десятичной системе: " << a.num;
}

void Coloring(int dataType) {
	const int escape = 27;
	const int enter = 13;
	const int keyRight = 77;
	const int keyLeft = 75;
	WORD colours[15] = {
	 FOREGROUND_BLUE,
	 FOREGROUND_GREEN,
	FOREGROUND_GREEN | FOREGROUND_BLUE,
	 FOREGROUND_RED,
	 FOREGROUND_RED | FOREGROUND_BLUE,
	FOREGROUND_RED | FOREGROUND_GREEN,
	 FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	FOREGROUND_INTENSITY,
	FOREGROUND_INTENSITY | FOREGROUND_BLUE,
	 FOREGROUND_INTENSITY | FOREGROUND_GREEN,
	FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
	FOREGROUND_INTENSITY | FOREGROUND_RED,
	  FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
	 FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
	 FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	};
	WORD colour;
	int from = 0, to, size = 1;
	bool ex = 1;
	char ch;
	while (ex) {
		gotoxy(0, 22);
		cout << "Номер старшего бита: < " << from << " >" << "\n\n";
		switch (ch = _getch()) {
		case keyRight: {
			if (from > 0) {
				from--;
			}
			break;
		}
		case keyLeft: {
			if ((dataType == 2) or (dataType == 3)) { //4 байта
				if (from < 31) {
					from++;
				}
			}
			else {
				if (from < 63) {
					_asm {
						mov eax, from
						inc from
					}
				}
			}
			break;
		}
		case enter: ex = 0; break;
		case escape: exit(0); break;
		default: break;
		}
	}
	ex = 1;
	while (ex) {
		gotoxy(0, 24);
		cout << "Размер группы бит: < " << size << " >" << "\n\n";
		switch (ch = _getch()) {
		case keyRight: {
			if ((dataType == 2) or (dataType == 3)) { //4 байта
				if (size < (from + 1)) {
					size++;
				}
			}
			else { //8 байт
				if (size < (from + 1)) {
					size++;
				}
			}
			break;
		}
		case keyLeft: {
			if (size > 1) {
				size--;
			}
			break;
		}
		case enter: ex = 0; break;
		case escape: exit(0); break;
		default: break;
		}
	}
	ex = 1;
	to = from - size + 1;
	int key = 0;                                            
	while (ex) {
		gotoxy(0, 26);
		cout << "Цвет: <";
		switch (key) {
		case 0: cout << " Темно - синий   >"; break;
		case 1: cout << " Темно - зеленый >"; break;
		case 2: cout << " Темный циан     >"; break;
		case 3: cout << " Темно - красный >"; break;
		case 4: cout << " Темная маджента >"; break;
		case 5:	cout << " Темно - желтый  >"; break;
		case 6:	cout << " Темно - серый   >"; break;
		case 7:	cout << " Серый           >"; break;
		case 8:	cout << " Синий           >"; break;
		case 9: cout << " Зеленый         >"; break;
		case 10: cout << " Циан           >"; break;
		case 11: cout << " Красный         >"; break;
		case 12: cout << " Маджента        >"; break;
		case 13: cout << " Желтый          >"; break;
		case 14: cout << " Белый           >"; break;
		default: break;
		}
		switch (ch = _getch()) {
		case keyRight: {
			if (key < 14) key++;
			if (key == 14) key = 1;
			break;
		}
		case keyLeft: {
			if (key > 0) key--;
			if (key == 0) key = 14;
			break;
		}
		case enter: ex = 0; break;
		case escape: exit(0); break;
		default: break;
		}
	}
	colour = colours[key];
	int plus;
	if ((dataType == 2) or (dataType == 3)) {
		plus = 32 - from;
	}
	else {
		plus = 64 - from;
	}
	setcolour(29 + plus, 9, size, colour); //биты с х = 31
}

template<typename T>
void Graph(T uninum) {
	unsigned int intMax = 2147483648;
	unsigned long long longIntMax = 9223372036854775808;
	HWND hWnd = FindWindowA("ConsoleWindowClass", NULL);
	HDC hdc = GetDC(hWnd);
	int j = 0;
	int bin[64] = { 0 };
	int w; //w - это сдвиг вбок
	if (sizeof(uninum.num) == 4) {
		w = 45;
		for (unsigned int i = intMax; i > 0; i >>= 1)
		{
			if (i & uninum.numInt)
			{
				bin[j] = 1;
			}
			else
			{
				bin[j] = 0;
			}
			j++;
		}
	} // если всего будет 32 бита, то ширина 45
	else {
		w = 20;
		for (unsigned long long i = longIntMax; i > 0; i >>= 1)
		{
			if (i & uninum.numInt)
			{
				bin[j] = 1;
			}
			else
			{
				bin[j] = 0;
			}
			j++;
		}
	} // если 64 бита, то ширина 20
	int mvX = 0, mvY = 220; // стартовые координаты
	for (int i = 0; i < sizeof(uninum.num) * 8; i++) //цикл от одного до 32 / 64
	{
		MoveToEx(hdc, mvX, mvY, 0); //ставим стартовую точку
		SetROP2(hdc, R2_WHITE); // выбираем линию
		if (bin[i] == 1 and bin[i + 1] == 0) //если элемент равен 1, а следующий 0, то
		{
			mvY += w; //к игреку прибавляем координату (чтобы нарисовать полосу вверх)
			LineTo(hdc, mvX, mvY); //рисуем полоску вверх
		}
		if (bin[i] == 0 and bin[i + 1] == 1) // если элемент равен 0, а следующий 1, то
		{
			mvY -= w;// убавляем игрек, чтобы нарисовать полоску вниз
			LineTo(hdc, mvX, mvY);
		}
		mvX += w; //в любом случае прибавляем по иксу, чтобы сдвинуть вправо
		LineTo(hdc, mvX, mvY); //рисуем направо
		/*ну и если не выполняется ни первое ни второе, то просто рисуем вправо*/
	}
}

template <typename T>
void menu2(T uninum, int dataType) {
	const int escape = 27;
	char ch, ex = 1;
	while (ex) {
		gotoxy(0, 20); //было 12 стало 20
		cout << "1 - циклический сдвиг; 2 - покраска битов; 3 - вывод графика" << "\n\n";
		ch = _getch();
		switch (ch) {
		case '1': {
			gotoxy(0, 22); emptystr(); //было 14 стало 22
			gotoxy(0, 24); emptystr();
			gotoxy(0, 26); emptystr();
			gotoxy(0, 28); emptystr();
			gotoxy(0, 30); emptystr();
			gotoxy(0, 32); emptystr();
			Shift(uninum, dataType);
			break; 
		}
		case '2': {
			gotoxy(0, 22); emptystr();
			gotoxy(0, 24); emptystr();
			gotoxy(0, 26); emptystr();
			gotoxy(0, 28); emptystr();
			gotoxy(0, 30); emptystr();
			gotoxy(0, 32); emptystr();
			Coloring(dataType);
			break; 
		}
		case '3': {
			gotoxy(0, 22); emptystr();
			gotoxy(0, 24); emptystr();
			gotoxy(0, 26); emptystr();
			gotoxy(0, 28); emptystr();
			gotoxy(0, 30); emptystr();
			gotoxy(0, 32); emptystr();
			Graph(uninum);
			break; 
		}
		case escape: ex = 0; break;
		default: break;
		}
	}
}

int main() {
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO structCursorInfo;
	GetConsoleCursorInfo(handle, &structCursorInfo);
	structCursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(handle, &structCursorInfo);
	const int space = 32;
	const int backspace = 8;
	const int escape = 27;
	const int enter = 13;
	const int keyRight = 77;
	const int keyLeft = 75;
	const int keyUp = 72;
	const int keyDown = 80;
	char alphabet[62] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
							'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
							'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
							'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D',
							'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
							'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
							'Y', 'Z' };
	while (true) {
		int dataType = 1, ex = 0, numSys = 10, startIndex = 0;
		char ch, ent[100];
		uniint number1;
		unifloat number2;
		unidouble number3;
		
		for (int i = 0; i < 100; i++) {
			ent[i] = 0;
		}
		do {
			system("cls");
			cout << "Char   "; if (dataType == 1) { cout << "<--"; }
			cout << "\n\n";	
			cout << "Int    "; if (dataType == 2) { cout << "<--"; } 
			cout << "\n\n";
			cout << "Float  "; if (dataType == 3) { cout << "<--"; }
			cout << "\n\n";
			cout << "Double "; if (dataType == 4) { cout << "<--"; }
			cout << "\n\n";

			ch = _getch();
			if (ch == 'а') {
				ch = _getch();
			}
			switch (ch)
			{
			case keyUp: if (dataType > 1) dataType--; break;
			case keyDown: if (dataType < 4) dataType++; break;
			case enter: ex = 1; break;
			case escape: exit(0); break;
			default:  break;
			}
		} while (ex == 0);

		if (dataType == 1) { //для char
			charout();
			continue;
		}

		ex = 0;
		do {
			system("cls");
			cout << "Выберите систему счисления от 2 до 62 (используйте стрелки влево и вправо): " << numSys;
			ch = _getch();
			if (ch == 'а') {
				ch = _getch();
			}
			switch (ch) {
			case keyLeft: if (numSys > 2) numSys--; break;
			case keyRight: if (numSys < 62) numSys++; break;
			case enter: ex = 1; break;
			case escape: exit(0);
			default: break;
			}
		} while (ex == 0);

		system("cls");
		cout << "Тип данных: ";
		switch (dataType) {
		case 2: cout << "int " << endl; break;
		case 3: cout << "float " << endl; break;
		case 4: cout << "double " << endl; break;
		default: break;
		}
		cout << "Система счисления: " << numSys << endl;
		cout << "Доступные символы: ";
		cout << "- ";
		if (dataType == 3 or dataType == 4) {
			cout << ". ";
		}
		for (int i = 0; i < numSys; i++) cout << alphabet[i] << " ";
		cout << endl;
		cout << "\n\n";
		cout << fixed << setprecision(99);
		switch (dataType) {
		case 2: {
			stringHandler(numSys, ent, startIndex, 0, alphabet);
			number1 = intHandling10(numSys, ent, startIndex, alphabet);
			cout << "\n\n";
			cout << "В десятичной системе счисления: ";
			cout << number1.num << "\n\n"; 
			cout << "В двоичной системе счисления: "; handling2(number1); 
			cout << "\n\n";
			menu2(number1, dataType);
			break;
		}
		case 3: {
			stringHandler(numSys, ent, startIndex, 1, alphabet);
			number2 = floatHandling10(numSys, ent, startIndex, alphabet);
			cout << "\n\n";
			cout << "В десятичной системе счисления: " << number2.num << "\n\n";
			cout << "В двоичной системе счисления: "; handling2(number2);
			cout << "\n\n";
			menu2(number2, dataType);
			break;
		}
		case 4: {
			stringHandler(numSys, ent, startIndex, 1, alphabet);
			number3 = doubleHandling10(numSys, ent, startIndex, alphabet);
			cout << "\n\n";
			cout << "В десятичной системе счисления: " << number3.num << "\n\n";
			cout << "В двоичной системе счисления: "; handling2(number3);
			cout << "\n\n";
			menu2(number3, dataType);
			break;
		}
		}
	}
	return 0;
}