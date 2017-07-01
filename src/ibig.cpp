/**
 *              Name("iBigMarket : Billing system");
 *  Description("Just a simple billing program with few options");
 *
 *      Programmed_by(1,"Madhurendra Sachan","XII","A2",30);
 *
 */

#include <iostream.h>

#include <iomanip.h>

#include <fstream.h>

#include <conio.h>

#include <string.h>

#include <stdio.h>

#include <dos.h>

#include <ctype.h>

#include <stdlib.h>

#define screenX 40

#define screenY 14

// prints a blank line with |      |

void msg_insertALine(int xPos,
                     int yPos,
                     int& lineCount,
                     char casc[],
                     int maxLen) {
  gotoxy(xPos, yPos + (++lineCount));

  cout << " " << casc[11] << " ";

  gotoxy(xPos + maxLen + 4, yPos + lineCount);

  cout << casc[11] << " ";

  gotoxy(xPos + 4, yPos + lineCount);
}

// prints a character n times

void msg_printNTimes(char toPrint, int n) {
  for (int i = 0; i < n; i++)

    cout << toPrint;
}

// prints a message box, operator overloading can be used for better experience
// :)

void msgbox(char title[],
            char msg[],
            int mode = 0,
            int xPos = -1,
            int yPos = -1) {
  clrscr();

  // int l=strlen(msg);cout<<l;getch();

  int maxLen = 6, maxHeight = 3;  // width & height of box

  // cout.write(msg,strlen(msg));

  // array with box element

  char casc[15];

  casc[1] = 'ɧ;casc[2] ='ͧ;
  casc[3] = '˧;casc[4] ='';

      casc[5] = '̧;         casc[6] ='Χ;
  casc[7] ='';

  casc[8] = 'ȧ;             casc[9] ='ʧ;
  casc[10] ='';

  casc[11] ='';

  int i = 0;

  int prePos = 0;

  // get max length of line & number of lines

  for (i = 0; msg[i] != '\0'; i++) {
    if (msg[i] == '\n' || i - prePos == 50) {
      if (maxLen < i - prePos)

        maxLen = i - prePos;

      if (i - prePos == 50)

        i--;

      prePos = i;

      maxHeight++;
    }
  }

  if (maxLen < i - prePos)

    maxLen = i - prePos;

  maxLen = maxLen + 3;

  if ((strlen(title) + 0 + 4) > (maxLen))

    maxLen = strlen(title) + 0 + 4;

  maxHeight = maxHeight + 4;

  if (maxLen % 2 == 0)
    maxLen += 1;

  // center postion box if xPos is -1 or yPos=-1

  if (xPos == -1)

    xPos = screenX - ((maxLen + 4 + 4) / 2);

  if (yPos == -1)

    yPos = screenY - ((maxHeight) / 2);

  gotoxy(xPos, yPos);

  // begin printing title

  cout << " " << casc[1] << casc[2];

  msg_printNTimes(casc[2], (maxLen - 0 - strlen(title) - 2) / 2);

  if ((maxLen - 0 - strlen(title) - 2) % 2)

    cout << casc[2] << " " << title << " " << casc[2];

  else

    cout << " " << title << " ";

  msg_printNTimes(casc[2], (maxLen - 0 - strlen(title) - 2) / 2);

  cout << casc[4] << " \n";

  int lineCount = 0;

  // leave few blank lines

  msg_insertALine(xPos, yPos, lineCount, casc, maxLen);

  msg_insertALine(xPos, yPos, lineCount, casc, maxLen);

  // print message

  prePos = 0;

  for (i = 0; msg[i] != '\0'; i++) {
    if (msg[i] == '\n' || i - prePos == 50) {
      msg_insertALine(xPos, yPos, lineCount, casc, maxLen);

      prePos = i;

      if (i - prePos == 50)

        i--;
    } else {
      cout << msg[i];
    }
  }

  // check for input mode

  if (mode == 1) {
    msg_insertALine(xPos, yPos, lineCount, casc, maxLen);

    msg_printNTimes('_', maxLen - 2);
  }

  msg_insertALine(xPos, yPos, lineCount, casc, maxLen);  // insert a fresh line

  gotoxy(xPos, yPos + (++lineCount));

  cout << ' ' << casc[8];
  msg_printNTimes(casc[2], maxLen - 11);
  cout << " iBigMarket " << casc[2] << casc[10] << ' ';  // bottom of box

  cin.clear();

  gotoxy(xPos + 4, yPos + lineCount - 2);  // move cursor to beg
}

// converts an number argument to character, type casting cannot be used

char* toChar(float num) {
  char str[10];

  ltoa(num, str, 10);

  return str;
}

// return potion of string needle in string haysack

int indexOf(char needle[], char haysack[]) {
  for (int i = 0; haysack[i] != '\0'; i++) {
    for (int j = 0; needle[j] != '\0'; j++)

      if (tolower(haysack[i + j]) !=
          tolower(needle[j]))  // if a character doesnot matches..continue with
                               // next char comaprison

        break;

      else if (needle[j + 1] == '\0')  // if end of needle is reached return pos

        return i;
  }

  return -1;
}

// class containing item description

class item_description {
 private:
  float value;  // value of item.usually price

  int total;  // total items in stock

  int sold;  // items sold

 public:
  char description[100];  // description of item,good for better search result

  char code[30], name[100];  // code & name of item

  char print();

  void in();

  // functions used to prevent illegal value,accessors & mutators

  float getValue() { return value; }

  void setValue(float f) {
    if (f > 0)
      value = f;
  }

  int getTotal() { return total; }

  void setTotal(int i) {
    if (i > total && i > 0)
      total = i;
  }

  int getSold() { return sold; }

  void setSold(int i) {
    if (i > 0) {
      sold += i;
      total -= i;
    }
  }

  // constructor to initalise

  item_description() {
    description[0] = code[0] = name[0] =
        '\0';  // ends the string as soon as it begins

    value = sold = total = 0;
  }
};

char item_description::print() {
  char message[1000] = "";

  strcat(message, "Code          : ");
  strcat(message, code);
  strcat(message, "\n");

  strcat(message, "Name          : ");
  strcat(message, name);
  strcat(message, "\n");

  strcat(message, "Description   : ");
  strcat(message, description);
  strcat(message, "\n");

  strcat(message, "Price/unit    : ");
  strcat(message, toChar(value));
  strcat(message, "\n");

  strcat(message, "Total unit(s) : ");
  strcat(message, toChar(total));
  strcat(message, "\n");

  strcat(message, "Sold unit(s)  : ");
  strcat(message, toChar(sold));
  strcat(message, "\n\nPress any key to continue...\0");

  msgbox("Item", message);

  return getch();
}

void item_description::in() {
  msgbox("Enter item code : ", "", 1);

  cin >> code;

  msgbox("Enter item name : ", "", 1);

  cin.ignore();  // clean the remaining \n in buffer

  cin.getline(name, 100);

  msgbox("Enter item description  : ", "", 1);

  cin.getline(description, 100);

  msgbox("Enter item value  : ", "", 1);

  cin >> value;

  msgbox("Enter items in stock  : ", "", 1);

  cin >> total;
}

// return description by item code

item_description getDescriptionById(char code[]) {
  item_description tmp;

  fstream f("items.db", ios::in | ios::binary);

  while (f.read((char*)&tmp, sizeof tmp)) {
    if (!strcmp(tmp.code, code))

      return tmp;

    else

      tmp.name[0] = '\0';
  }

  f.close();

  return tmp;
}

void removeDescription() {
  item_description tmp;

  char code[30];

  msgbox("Enter item code : ", "", 1);

  cin >> code;

  ifstream i("items.db", ios::in | ios::binary);

  ofstream f("items.tmp.db", ios::out | ios::binary);

  while (i.read((char*)&tmp, sizeof tmp)) {
    if (strcmp(tmp.code, code) != 0)

      f.write((char*)&tmp, sizeof tmp);
  }

  i.close();

  f.close();

  remove("items.db");

  rename("items.tmp.db", "items.db");
}

void modifyDescription() {
  item_description tmp;

  char code[30];

  msgbox("Enter item code : ", "", 1);

  cin >> code;

  fstream f("items.db", ios::in | ios::out | ios::binary);

  while (f.read((char*)&tmp, sizeof tmp)) {
    if (!strcmpi(tmp.code, code)) {
      float var;

      msgbox("Enter item new value  : ", "");

      cin >> var;

      tmp.setValue(var);

      msgbox("Enter items to add in stock  : ", "");

      cin >> var;

      tmp.setTotal(tmp.getTotal() + (int)var);

      tmp.print();

      f.seekp(f.tellg() - sizeof(tmp));  // move one object back

      f.write((char*)&tmp, sizeof(tmp));  // overwrite the object with new

      break;
    }
  }

  f.close();
}

void searchDescription() {
  char keyword[100];

  msgbox("Enter keyword to search (description,code) :", "", 1);

  cin >> keyword;

  msgbox("Info",
         "Anytime press 'x' to exit from search.\nor any key to "
         "continue to next result.\n\nPress any key to continue...");

  getch();

  fstream f("items.db", ios::in | ios::binary);

  item_description tmp;

  while (f.read((char*)&tmp, sizeof tmp))

    if ((!strcmpi(tmp.code, keyword)) ||
        indexOf(keyword, tmp.description) > -1 ||
        indexOf(keyword, tmp.name) > -1)

      if (tmp.print() == 'x')

        break;

  f.close();
}

void addDescription() {
  item_description tmp;

  tmp.in();

  tmp.print();

  fstream f("items.db", ios::out | ios::app | ios::binary | ios::ate);

  f.write((char*)&tmp, sizeof tmp);

  f.close();
}

void codeGetDescription() {
  char code[30];

  msgbox("Enter item code : ", "", 1);

  cin >> code;

  item_description tmp = getDescriptionById(code);

  if (tmp.name[0] != '\0')

    tmp.print();
}

void manageItems() {
  char ch;

  do {
    msgbox(" Manage Items ! ",
           "1. Add Item \n2. Modify Item\n3. Remove "
           "Item\n4. Search Item \n5. Item by Code\n6. "
           "Back");

    ch = tolower(getch());

    if (ch == '1' || ch == 'a')

      addDescription();

    else if (ch == '2' || ch == 'r')

      modifyDescription();

    else if (ch == '3' || ch == 'c')

      removeDescription();

    else if (ch == '4' || ch == 's')

      searchDescription();

    else if (ch == '5' || ch == 'i')

      codeGetDescription();

    if (ch == '6' || ch == 'x' || ch == 'b')

      break;

  } while (1);
}

class item : public item_description {  // inherit description class

 public:
  int quantity;

  float amount;

  item() {
    strcpy(code, "");

    strcpy(name, "");

    quantity = 0;

    amount = 0;
  }

  void print();

  int in();
};

int item::in() {
  msgbox("Enter item code : ", "", 1);

  cin >> code;

  item_description tmp;

  tmp = getDescriptionById(code);

  if (tmp.name[0] == '\0')

    return 0;

  msgbox("Enter quantity  : ", "", 1);

  cin >> quantity;

  strcpy(name, tmp.name);

  setValue(tmp.getValue());

  amount = quantity * getValue();

  print();

  return 1;
}

void item::print() {
  char message[500] = "";

  strcat(message, "Code     : ");
  strcat(message, code);
  strcat(message, "\n");

  strcat(message, "Name     : ");
  strcat(message, name);
  strcat(message, "\n");

  strcat(message, "Quantity : ");
  strcat(message, toChar((float)quantity));
  strcat(message, "\n");

  strcat(message, "Amount   : ");
  strcat(message, toChar(amount));
  strcat(message, "\n\nPress any key to continue...\0");

  msgbox("Item", message);

  getch();
}

void itemSold(item bill[], int cnt) {
  item_description tmp;

  fstream f("items.db", ios::in | ios::out | ios::binary);

  while (f.read((char*)&tmp, sizeof tmp))

    for (int i = 0; i < cnt; i++)

      if ((!strcmpi(tmp.code, bill[i].code)) && bill[i].quantity) {
        tmp.setSold(bill[i].quantity);  // decrease total & increase sold

        f.seekp(f.tellg() - sizeof(tmp));  // move one object back

        f.write((char*)&tmp, sizeof(tmp));  // rewrite with new object

        break;
      }

  f.close();
}

void printReceipt(item bill[], int cnt, float paid) {
  itemSold(bill, cnt);

  clrscr();

  float total = 0;

  cout << "\n";

  cout << setw(55)
       << "------------------- Bill : iBigMarket -------------------"
       << "\n\n";

  cout << setw(12) << "Code "
       << " | " << setw(22) << "Name"
       << " | " << setw(15) << "Amount" << endl;

  cout << setw(12) << "----------"
       << " | " << setw(22) << "--------------------"
       << " | " << setw(15) << "------------" << endl;

  for (int i = 0; i < cnt; i++) {
    if (bill[i].quantity > 0) {
      cout << setw(12) << bill[i].code << " | " << setw(22) << bill[i].name
           << " | " << setw(5) << bill[i].quantity << "*" << bill[i].getValue()
           << "=" << setw(6) << bill[i].amount << endl;

      total += bill[i].amount;
    }
  }

  cout << setw(55)
       << "========================================================="
       << "\n";

  cout << setw(45) << " Total  : " << total << "\n";

  cout << setw(45) << " Paid   : " << paid << '\n';

  cout << setw(45) << " Return : " << paid - total << '\n';

  cout << setw(55)
       << "----------------------- Thank You -----------------------"
       << "\n";

  cout << "\n\n Press any key to continue...";

  getch();
}

void removeItem(item bill[], int cnt) {
  char code[30];

  msgbox("Enter item code : ", "", 1);

  cin >> code;

  for (int x = 0; x < cnt; x++)

    if (strcmpi(code, bill[x].code) == 0)

      bill[x].quantity = 0;
}

float checkOut() {
  char paid[10] = "\0";

  msgbox("Checkout !", "Enter amount paid : \n", 1);

  cin >> paid;

  float amount = 0;

  amount = strtod(paid, NULL);

  return amount;
}

void newInvoice() {
  char ch;

  item bill[30];  // max items in bill =30

  int i = 0;  // items counter

  do {
    msgbox(" Invoice !", "1. Add Item\n2. Remove Item\n3. CheckOut\n4. Cancel");

    ch = tolower(getch());

    if (ch == '1' || ch == 'a') {
      if (!bill[i++].in())

        i--;
    } else if (ch == '2' || ch == 'r') {
      removeItem(bill, i);
    } else if (ch == '3' || ch == 'c') {
      if (i > 0) {
        float paid = 0;

        paid = checkOut();

        if (paid > 0) {
          printReceipt(bill, i, paid);

          ch = 'x';
        }
      }
    }

    if (ch == '4' || ch == 'x')

      break;

  } while (1);
}

int main() {
  char ch;

  do {
    msgbox(" Welcome !", "1. Sell \n2. Manage \n3. Help \n4. About\n5. Exit");

    ch = tolower(getch());

    if (ch == '1' || ch == 's')

      newInvoice();

    else if (ch == '2' || ch == 'm')

      manageItems();

    else if (ch == '3' || ch == 'h') {
      clrscr();

      msgbox("Help !",
             "To select option press the option number\nor simply "
             "first letter of option.\nNote : To Exit press "
             "'x'\n\nPress any key to continue...");

      getch();
    } else if (ch == '4' || ch == 'a') {
      int i = 2, x = 0;

      do {
        clrscr();

        msgbox(" About !",
               "      iBigMarket\n   Version : 1.0 beta\n Credits "
               ": Computer Teacher\nPress any key to continue...",
               0, i);

        delay(100);

        if (x == 0 && i < (screenX - 30))

          if (++i == (screenX - 30))

            x++;

        if (x == 1 && i > 1)

          if (--i == 1)

            x = 0;

        if (kbhit())

          break;

      } while (1);

      getch();  // will get input from buffer, so clears buffer
    } else if (ch == '5' || ch == 'x')

      break;

  } while (1);

  return 0;
}
