#include "Orders.h"


 //The labels of the orders, which are constant and static.
 
const string deploy::label = "Deploy";
const string advanceOrder::label = "Advance";
const string bomb::label = "Bomb";
const string blockade::label = "Blockade";
const string airlift::label = "Airlift";
const string negotiate::label = "Negotiate";

// Default constructor of OrderList, designed to hold a list of valid orders and carry out basic list functions

OrdersList::OrdersList()
{
}

//OrderList destructor

OrdersList::~OrdersList()
{
    int listSize = orders.size();

    for (int i = 0; i < listSize; i++) // Delete memory for orders, which are always dynamically allocated.
        delete orders[i];
}

/**
 * Copy constructor: makes a deep copy of a list
 * @param oldList
 */
OrdersList::OrdersList(const OrdersList& oldList)
{
    int listSize = oldList.orders.size();
    orders = vector<Order*>(listSize);

    for (int i = 0; i < listSize; i++) // Same objects, but in different memory locations.
        orders[i] = oldList.orders[i]->clone();

    cout << "The list has been copied!" << endl;
}


// Order Constructors
Order::Order() = default;
Order::Order(const Order&)
{
}

 //Destructors
Order::~Order()
{
}

deploy::~deploy()
{
    delete this->player;
    delete this->target;
}

advanceOrder::~advanceOrder()
{
    delete this->player;
    delete this->source;
    delete this->target;
    delete this->enemy;
}

bomb::~bomb()
{
    delete this->player;
    delete this->target;
    delete this->hand;
    delete this->deck;
}

blockade::~blockade()
{

}

airlift::~airlift()
{

}

negotiate::~negotiate()
{

}

// @param o Method that adds an order to the orders vector

void OrdersList::addOrder(Order* o)
{
    if (o == nullptr) // See OrderOperation.
        cout << "This is a null pointer! Adding operation failed!" << endl;
    else
    {
        orders.push_back(o);
        cout << "Order has been added to the list! Your list now looks like: \n";
        cout << *this << endl;
    }
}

/**
 * Method that deletes an order
 * @param pos
 */
void OrdersList::remove(int pos)
{
    int listSize = orders.size();

    if (listSize == 0) // Empty list so nothing to be done.
        cout << "Nothing to erase!" << endl;
    else if (pos > listSize || pos < 1) // Bounds check.
        cout << "Please select a valid position!" << endl;
    else
    {
        delete orders[pos - 1]; // Order objects are dynamically allocated, so frees memory.
        orders.erase(orders.begin() + pos - 1); // Once memory freed, delete actual pointer from list.
        cout << "Erase at position " << pos << " successful! Your list now looks like: \n";
        cout << *this << endl;
    }
}

/**
 * Method that moves an order
 * @param pos1
 * @param pos2
 */
void OrdersList::move(int pos1, int pos2)
{
    int listSize = orders.size(); // Compute size to check if a move can be performed.

    if (listSize == 0) // Empty list so nothing to be done.
        cout << "There is nothing to move!" << endl;
    else if (listSize == 1) // Only 1 item in the list, so nothing to be done.
        cout << "You need at least two orders to perform a swap!" << endl;
    else if (pos1 > listSize || pos2 > listSize || pos1 < 1 || pos2 < 1) // Bounds check.
        cout << "One or both of your positions are invalid!" << endl;
    else
    {
        Order* temp = orders[pos1 - 1]; // Swap pointers. Address of actual object unchanged.
        orders[pos1 - 1] = orders[pos2 - 1];
        orders[pos2 - 1] = temp;
        cout << "Order " << pos1 << " and Order " << pos2 << " have been swapped! Your list now looks like: \n";
        cout << *this << endl;
    }
}

/**
 * Method that executes an order
 */
void OrdersList::executeOrders()
{
    int listSize = orders.size();

    if (listSize == 0)
        cout << "Nothing to execute!" << endl;
    else
    {
        for (int i = 0; i < listSize; i++)
        {
            orders[i]->execute();
            delete orders[i];
        }

        orders.clear();
        cout << "Orders have been executed!" << endl;
    }
}

/**
 * Assignment operator
 * @param rhsList
 * @return
 */
OrdersList& OrdersList::operator=(const OrdersList& rhsList) // Releases resources by LHS and deep-copy
{                                                            // to RHS
    if (&rhsList == this) // Checks for self assignment
        return *this;

    int lhsListSize = orders.size();
    int rhsListSize = rhsList.orders.size();

    for (int i = 0; i < lhsListSize; i++)
        delete orders[i];

    orders = vector<Order*>(rhsListSize); // Reallocate memory for vector of size RHS

    for(int i = 0; i < rhsListSize; i++)
        orders[i] = rhsList.orders[i]->clone(); // Clone RHS element into LHS

    return *this;
}

/**
 * Prints the list using cout.
 * @param strm
 * @param ol
 * @return
 */
ostream& operator<<(ostream& out, const OrdersList& ol)
{
    int listSize = ol.orders.size(); // For iteration
    const int MAX_WIDTH = 9; // To force the amount of space a string takes.
    const char separator = ' '; // If string.length() < 9, fill with empty spaces.

    for (int i = 0; i < listSize; i++)
        out << left << setw(MAX_WIDTH) << setfill(separator) << i + 1 << " | "; // Left formatted

    out << "\n";

    for (int i = 0; i < listSize; i++)
        out << left << setw(MAX_WIDTH) << setfill(separator) << ol.orders[i]->getLabel() << " | ";

    out << "\n";

    return out;
}

//OrdersList input stream operator
istream& operator>>(istream& in, OrdersList&)
{
    return in;
}

//deploy constructors
deploy::deploy()
{
    this->player = new Player();
    this->target = new Territory();
    this->reinforcements = 0;
}

deploy::deploy(Player* player, Territory* target, const int& reinforcements)
{
    this->player =player;
    this->target =target;
    this->reinforcements = reinforcements;
}

deploy::deploy(const deploy& other)
{
    this->player = other.player;
    this->target = other.target;
    this->reinforcements = other.reinforcements;
}

//deploy class operator
deploy& deploy::operator=(const deploy other)
{
    if (this != &other) {

        //Freeing existing resources
        delete this->player;
        delete this->target;

        //Copying the data
        this->player = other.player;
        this->target = other.target;
        this->reinforcements = other.reinforcements;

    }
    
    return *this;
}

/**
 * Returns the label of the order.
 * @return
 */
string deploy::getLabel() const
{
    return label;
}



//advance constructors
advanceOrder::advanceOrder()
{
    this->player = new Player();
    this->source = new Territory();
    this->target = new Territory();
    this->enemy = new Player();
    this->numberArmies = 0;

}

advanceOrder::advanceOrder(Player* player, Territory* source, Territory* target, Player* enemy, const int& numberArmies)
{
    this->player = player;
    this->source = source;
    this->target = target;
    this->enemy = enemy;
    this->numberArmies = numberArmies;
}

advanceOrder::advanceOrder(const advanceOrder& other)
{
    this->player = other.player;
    this->source = other.source;
    this->target = other.target;
    this->enemy = other.enemy;
    this->numberArmies = other.numberArmies;
}
//advance class operator
advanceOrder& advanceOrder::operator=(const advanceOrder other)
{
    //Freeing existing resources
    delete this->player;
    delete this->source;
    delete this->target;
    delete this->enemy;

    //Copying the data
    this->player = other.player;
    this->source = other.source;
    this->target = other.target;
    this->enemy = other.enemy;
    this->numberArmies = other.numberArmies;


    return *this;
}

/**
 * Returns the label of the order.
 * @return
 */
string advanceOrder::getLabel() const
{
    return label;
}

//bomb constructors
bomb::bomb()
{
    this->player = new Player();
    this->target = new Territory();
    this->hand = new Hand();
    this->deck = new Deck();
}

bomb::bomb(Player* player, Territory* target, Hand* hand, Deck* deck)
{
    this->player = player;
    this->target = target;
    this->hand = hand;
    this->deck = deck;
}

bomb::bomb(const bomb& other)
{
    this->player = other.player;
    this->target = other.target;
    this->hand = other.hand;
    this->deck = other.deck;
}

//bomb class operator
bomb& bomb::operator=(const bomb other)
{
    //Freeing existing resources
    delete this->player;
    delete this->target;
    delete this->hand;
    delete this->deck;

    //Copying the data
    this->player = other.player;
    this->target = other.target;
    this->hand = other.hand;
    this->deck = other.deck;

    return *this;
}

/**
 * Returns the label of the order.
 * @return
 */
string bomb::getLabel() const
{
    return label;
}

//blockade constructors
blockade::blockade()
{
}

blockade::blockade(const blockade&)
{
}

//blockade class operator
blockade& blockade::operator=(const blockade)
{
    return *this;
}

/**
 * Returns the label of the order.
 * @return
 */
string blockade::getLabel() const
{
    return label;
}

//airlift constructors
airlift::airlift()
{
}

airlift::airlift(const airlift&)
{
}

//airlift class operator
airlift& airlift::operator=(const airlift)
{
    return *this;
}

/**
 * Returns the label of the order.
 * @return
 */
string airlift::getLabel() const
{
    return label;
}

//negotiate constructors
negotiate::negotiate()
{
}

negotiate::negotiate(const negotiate&)
{
}

//negotiate class operator
negotiate& negotiate::operator=(const negotiate)
{
    return *this;
}

/**
 * Returns the label of the order.
 * @return
 */
string negotiate::getLabel() const
{
    return label;
}

/**
 * Works in conjunction with printOrder() from subclasses to polymorphically
 * give information about a specific order using cout.
 * @param strm
 * @param o
 * @return
 */
ostream& operator<<(ostream& out, const Order& o)
{
    return o.printOrder(out);
}

istream& operator>>(istream& in, Order&)
{
    return in;
}

ostream& operator<<(ostream& out, const deploy& d)
{
    return d.printOrder(out);
}

istream& operator>>(istream& in, deploy&)
{
    return in;
}

ostream& operator<<(ostream& out, const advanceOrder& a)
{
    return a.printOrder(out);
}

istream& operator>>(istream& in, advanceOrder&)
{
    return in;
}

ostream& operator<<(ostream& out, const bomb& b)
{
    return b.printOrder(out);
}

istream& operator>>(istream& in, bomb&)
{
    return in;
}

ostream& operator<<(ostream& out, const blockade& b)
{
    return b.printOrder(out);
}

istream& operator>>(istream& in, blockade&)
{
    return in;
}

ostream& operator<<(ostream& out, const airlift& a)
{
    return a.printOrder(out);
}

istream& operator>>(istream& in, airlift&)
{
    return in;
}

ostream& operator<<(ostream& out, const negotiate& n)
{
    return n.printOrder(out);
}

istream& operator>>(istream& in, negotiate&)
{
    return in;
}

ostream& operator<<(ostream& out, const OrderOperation& o)
{
    return out;
}

istream& operator>>(istream& in, OrderOperation&)
{
    return in;
}




/**
 * Does not print anything useful for this assignment.
 * @param out
 * @return
 */
ostream& deploy::printOrder(ostream& out) const
{
    return out << "deploy order!";
}

ostream& advanceOrder::printOrder(ostream& out) const
{
    return out << "advance order!";
}

ostream& bomb::printOrder(ostream& out) const
{
    return out << "bomb order!";
}

ostream& blockade::printOrder(ostream& out) const
{
    return out << "blockade order!";
}

ostream& airlift::printOrder(ostream& out) const
{
    return out << "airlift order!";
}

ostream& negotiate::printOrder(ostream& out) const
{
    return out << "negotiate order!";
}

/**
 * For this assignment, validation is not defined.
 * @return
 */
bool deploy::validate() const
{

    cout << "Validating Deploy...\n";

    bool owned=false;
    bool enoughArmies=false;
    for (auto territory : player->getPlayerTerritories()) {
        if (target->getOwner() == territory->getOwner()) {
            owned = true;
            break;
        }
    }
    if (!owned) {
        cout << "Territory" << *target << " is not owned by Player " << player->getPlayerName() << endl;
    }
    /*if (reinforcements <= player->getReinforcements()) {
        enoughArmies = true;
    }
    else {
        cout << "Player " << player->getPlayerName() << " does not have enough reinforcements to deploy " 
             << reinforcements << " armies" << endl;
    }*/
   
    return owned && enoughArmies;

}

bool advanceOrder::validate() const
{
    cout << "Validating Advance...\n";

    bool owned = false;
    bool is_neighbour = false;
    bool enough_units = false;

    for (auto territory : player->getPlayerTerritories()) {
        if (source->getID() == territory->getID()) {
            owned = true;
            break;
        }
    }
    if (!owned) {
        cout << "Source " << *source << " is not owned by " << *player << endl;
    }
    // must check that target territory is a neightb
    for (auto neighbour : source->getNeighbours()) {
        if (target->getID() == neighbour->getID()) {
            is_neighbour = true;
            break;
        }
    }
    if (!is_neighbour) {
        cout << "Target " << *target << " is not a neighbour of source " << *source << endl;
    }
    // must check if player has enough units on source territory
    if (numberArmies <= source->getNumberArmies() - 2) {
        enough_units = true;
    }
    else {
        cout << "Source " << *source << " does not have the sufficient armies requested " << endl;
    }

    return owned && is_neighbour && enough_units;

}

bool bomb::validate() const
{
    cout << "Validating Bomb...\n";
    
    bool target_owned = false;
    bool has_card = false;
    bool is_neighbour = false;
    
    //Must check that the target is not owned by the player issuing the order
    for (auto territory : player->getPlayerTerritories()) {
        if (target->getOwner() == territory->getOwner()) {
            target_owned = true;
            break;
        }
    }
    if (target_owned) {

        cout << "Territory" << *target << " is owned by Player " << player->getPlayerName() << endl;
    }

    //NOTE: Accessor for list of cards at hand probably needed
    
    while (!is_neighbour) {
        for (auto territory : player->getPlayerTerritories()) {
            for (auto neighbour : territory->getNeighbours()) {
                if (target->getID() == neighbour->getID()) {
                    is_neighbour = true;
                }
            }
        }
        break;
    }
    return !target_owned && has_card && is_neighbour;
}

bool blockade::validate() const
{
    cout << "Validating Blockade...\n";
    return true;
}

bool airlift::validate() const
{
    cout << "Validating Airlift...\n";
    return true;
}

bool negotiate::validate() const
{
    cout << "Validating Negotiate...\n";
    return true;
}

/**
 * Validates an order and proceeds accordingly. For this assignment, execution is not defined.
 */
void deploy::execute() const
{
    if (!validate()) {
        cout << "Deploy order cannot be executed" << endl;
        return;
    }
    cout << "Performing " << *this << endl;

    // transfer units from reinforcement pool
    target->setNumberArmies(target->getNumberArmies() + reinforcements);
    //player->removeReinforcements(reinforcements);
}

void advanceOrder::execute() const
{
    if (!validate()) {
        cout << "Advance order cannot be executed" << endl;
        return;
    }
    cout << "Performing " << *this << endl;
    
    /*
    Seeing if target territory belongs to player issuing the order. 
    Execution stops if they match
    */
    for (auto territory : player->getPlayerTerritories()) {
        if (target->getID() == territory->getID()) {
            target->setNumberArmies(target->getNumberArmies() + numberArmies);
            source->setNumberArmies(source->getNumberArmies() - numberArmies);
            return;
        }
    }
    // We now know the target is an enemy
    srand(time(NULL)); // initial random seed
    // Continue attacks until one territory is out of armies
    
    while (source->getNumberArmies() - numberArmies > 2 && target->getNumberArmies() > 0) {
        int attack_chance = rand() % 100 + 1;
        if (attack_chance < 60) {  // 60% chance
            target->setNumberArmies(target->getNumberArmies() - 1);
        }
        int defend_chance = rand() % 100 + 1;
        if (defend_chance < 70) {  // 70% chance
            source->setNumberArmies(source->getNumberArmies() - 1);
        }
    }
    /*
    Ownership of territory is transferred to the attacking player, and
    surviving soldiers from the attacking side are transferred to the gained territoty
    */
    if (target->getNumberArmies() == 0) {

        target->setOwner(player);
        target->setNumberArmies(source->getNumberArmies() - numberArmies);
        for (int i = 0; 0 < enemy->getPlayerTerritories().size(); i++) {

            if (enemy->getPlayerTerritories().at(i)->getID() == target->getID()) {

                enemy->getPlayerTerritories().erase(enemy->getPlayerTerritories().begin()+i);
                player->addTerritory(target);
                
            }

        }

        player->getPlayerHand()->add(new Card(0));
        
    }
}

void bomb::execute() const
{
    if (!validate())
    {
        cout << "Bomb order cannot be executed!\n";
        return;
    }
    cout << "Performing " << *this << endl;
    // play card from hand - it has already been checked in validate
    Card* card = new Card(0);
    player->getPlayerHand()->remove(0); //Placeholder. Necessary to make sure that card returns to deck after use.

    //Bombs terrritory. Number of armies reduced to half
    target->setNumberArmies(floor(target->getNumberArmies() / 2));


}

void blockade::execute() const
{
    if (validate())
        cout << "Blockade is being executed!\n";
}

void airlift::execute() const
{
    if (validate())
        cout << "Airlift is being executed!\n";
}

void negotiate::execute() const
{
    if (validate())
        cout << "Negotiate is being executed!\n";
}

/**
 * Since we have a list of pointers to an abstract class,
 * we need a way to polymorphically clone the objects in the
 * list if we ever decide to deep-copy the list. Calls the
 * compiler-generated copy constructor, which is OK since
 * these subclasses don't have object specific data members.
 * @return
 */
Order* deploy::clone() const
{
    return new deploy(*this);
}

Order* advanceOrder::clone() const
{
    return new advanceOrder(*this);
}

Order* bomb::clone() const
{
    return new bomb(*this);
}

Order* blockade::clone() const
{
    return new blockade(*this);
}

Order* airlift::clone() const
{
    return new airlift(*this);
}

Order* negotiate::clone() const
{
    return new negotiate(*this);
}

//OrderOperation constructors
OrderOperation::OrderOperation()
{
}

OrderOperation::OrderOperation(const OrderOperation&)
{
}

//OrderOperation class operator
OrderOperation& OrderOperation::operator=(const OrderOperation)
{
    return *this;
}

//OrderOperation destructor
OrderOperation::~OrderOperation()
{
}

/**
 * Creates an order based on user input. Only the strings below
 * are the possible orders in this game. If the user inputs a
 * string different than those listed, it returns a null pointer,
 * which is meant to be handled in OrdersList::addOrder().
 * 
 * Based on the instruction, valid orders for this game are mentioned below 'strings' (user input) 
 * If else it will return null pointer and handled in OrderList::addOrder().
 * @param orderType
 * @return
 */
Order* OrderOperation::createOrder(string orderType) const
{
    if (orderType == "deploy")
        return new deploy;
    else if (orderType == "advance")
        return new advanceOrder;
    else if (orderType == "bomb")
        return new bomb;
    else if (orderType == "blockade")
        return new blockade;
    else if (orderType == "airlift")
        return new airlift;
    else if (orderType == "negotiate")
        return new negotiate;
    else
        return nullptr;
}
