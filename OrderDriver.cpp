#include "../Orders.h"


/*Free function of driver class. When invoked, it will create a list of orders, each of a different subclass,
and test several of the features of the OrdersList class, which includes addOrder, remove, and move*/
void testOrderLists() {

    OrderOperation operate;
    OrdersList list;

    cout << "\n------------ ADDING ORDERS --------------\n" << endl;

    list.addOrder(operate.createOrder("deploy"));
    list.addOrder(operate.createOrder("advance"));
    list.addOrder(operate.createOrder("bomb"));
    list.addOrder(operate.createOrder("blockade"));
    list.addOrder(operate.createOrder("airlift"));
    list.addOrder(operate.createOrder("negotiate"));

    cout << "\n------------ DELETING ORDERS -------------\n" << endl;

    list.remove(1);
    list.remove(5);
    list.remove(3);

    cout << "\n------------ MOVING ORDERS -------------\n" << endl;

    list.move(1, 3);
    list.move(2, 1);
    list.move(3, 2);

    cout << "\n------------ COPYING LIST USING COPY C'TOR ------------\n" << endl;

    OrdersList ctorList = OrdersList(list);
    cout << ctorList;

    cout << "\n------------- COPYING LIST USING = OPERATOR --------------\n" << endl;

    OrdersList a;
    a.addOrder(operate.createOrder("deploy"));
    a.addOrder(operate.createOrder("bomb"));
    a = list;
    cout << a;

    cout << "\n------------ EXECUTING ORDERS FROM LIST ------------\n";

    list.executeOrders();

    cout << "\n------------- PRINTING ALL THE LISTS --------------\n";

    cout << "Printing the original list!:\n" << list << endl;
    cout << "Printing the c'tor list!:\n" << ctorList << endl;
    cout << "Printing = operator list!:\n" << a << endl;

    cout << "\n********** PRINTING ALL THE LISTS AGAIN + OPERATIONS **********\n";

    list.addOrder(operate.createOrder("deploy"));
    list.addOrder(operate.createOrder("airlift"));
    ctorList.remove(2);
    cout << "Printing the original list!:\n" << list << endl;
    cout << "Printing the c'tor list!:\n" << ctorList << endl;
    cout << "Printing = operator list!:\n" << a << endl;
}

int main()
{

    testOrderLists();

    /*OrderOperation operate;
    OrdersList list;
    cout << "\n------------ ADDING ORDERS --------------\n" << endl;
    
    list.addOrder(operate.createOrder("deploy"));
    list.addOrder(operate.createOrder("advance"));
    list.addOrder(operate.createOrder("bomb"));
    list.addOrder(operate.createOrder("blockade"));
    list.addOrder(operate.createOrder("airlift"));
    list.addOrder(operate.createOrder("negotiate"));
    cout << "\n------------ DELETING ORDERS -------------\n" << endl;
    list.remove(1);
    list.remove(5);
    list.remove(3);
    cout << "\n------------ MOVING ORDERS -------------\n" << endl;
    list.move(1, 3);
    list.move(2, 1);
    list.move(3, 2);
    cout << "\n------------ COPYING LIST USING COPY C'TOR ------------\n" << endl;
    OrdersList ctorList = OrdersList(list);
    cout << ctorList;
    cout << "\n------------- COPYING LIST USING = OPERATOR --------------\n" << endl;
    OrdersList a;
    a.addOrder(operate.createOrder("deploy"));
    a.addOrder(operate.createOrder("bomb"));
    a = list;
    cout << a;
    cout << "\n------------ EXECUTING ORDERS FROM LIST ------------\n";
    list.executeOrders();
    cout << "\n------------- PRINTING ALL THE LISTS --------------\n";
    cout << "Printing the original list!:\n" << list << endl;
    cout << "Printing the c'tor list!:\n" << ctorList << endl;
    cout << "Printing = operator list!:\n" << a << endl;
    cout << "\n********** PRINTING ALL THE LISTS AGAIN + OPERATIONS **********\n";
    list.addOrder(operate.createOrder("deploy"));
    list.addOrder(operate.createOrder("airlift"));
    ctorList.remove(2);
    cout << "Printing the original list!:\n" << list << endl;
    cout << "Printing the c'tor list!:\n" << ctorList << endl;
    cout << "Printing = operator list!:\n" << a << endl;*/

    return 0;
}
