#include <cstdio>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

enum Shape {
    Clubs,
    Diamonds,
    Hearts,
    Spades
};

class Card {
    public:
        int number;
        Shape shape;

        Card(int num, Shape s) {
            number = num;
            shape = s;
        }

        friend ostream& operator<< (ostream &out, const Card &card) {
            switch (card.number) {
                case 1:
                    out << "Ace";
                    break;
                case 11:
                    out << "Jack";
                    break;
                case 12:
                    out << "Queen";
                    break;
                case 13:
                    out << "King";
                    break;
                default:
                    out << card.number;
            }

            out << " of ";
            switch (card.shape) {
                case Clubs:
                    out << "Clubs";
                    break;
                case Diamonds:
                    out << "Diamonds";
                    break;
                case Hearts:
                    out << "Hearts";
                    break;
                case Spades:
                    out << "Spades";
                    break;
            }

            return out;
        }
};

class CardCollection {
    public:
        vector<Card*> cards;

        ~CardCollection() {
            for (auto it: cards) {
                delete it;
            }
        }

        Card* operator [](int index) {
            return this->cards[index];
        }

        Card* upper() {
            return cards.back();
        }

        void push(Card* c) {
            cards.push_back(c);
        }

        Card* pop() {
            Card* card = cards.back();
            cards.pop_back();
            return card;
        }

        int size() {
            return this->cards.size();
        }

        void shuffle() {
            srand(time(0));
            random_shuffle(cards.begin(), cards.end());
        }

        void print() {
            for (Card* it: cards) {
                cout << *it << endl;
            }
        }
};

class Deck: public CardCollection {
    private:
        const int NUM_CARD_NUMBERS = 13;
        const int NUM_CARD_SHAPES = 4;
        const int NUM_CARDS = NUM_CARD_NUMBERS * NUM_CARD_SHAPES;
    public:
        Deck() {
            for (int i = 1; i <= NUM_CARD_NUMBERS; ++i) {
                for (int j = Clubs; j <= Spades; ++j) {
                    Shape shape = static_cast<Shape>(j);

                    Card *card = new Card(i, shape);
                    cards.push_back(card);
                }
            }
        }

        virtual ~Deck() {
        }
};

class Player {
    public:
        CardCollection hand;

        void printOptions() {
            cout << "Here are your options:" << endl;
            cout << "----------------------" << endl;
            for (int i = 0; i < hand.size(); ++i) {
                cout << "(" << i + 1 << ") ";
                cout << *hand[i] << endl;
            }
        }

        void evalOption(int i) {
        }
};

class ComputerPlayer : Player {
};

class HumanPlayer : Player {
};

class Game {
    public:
        vector<Player*> players;
        Deck* deck;
        CardCollection table;

        Game(int num_players) {
            deck = new Deck();
            deck->shuffle();

            for (int i = 0; i < num_players; ++i) {
                players.push_back(new Player());
            }
        }

        void share() {
            if (deck->size() % players.size()) {
                cout << "Warning: deck can't be shared equally" << endl;
                return;
            }

            for (auto player : players) {
                for (int i = 0; i < 7; ++i) {
                    player->hand.push(deck->pop());
                }
            }

        }

        ~Game() {
            delete deck;
        }

        void play() {
            share();
            table.push(deck->pop());
        }

        void nextRound(Player* player) {
            Card* c = deck->pop();
            player->hand.push(c);

            cout << "Next round" << endl << "===========" << endl;
            cout << "The upper card is " << *table.upper() << endl;
            cout << "----------------------------------------------" << endl;
            cout << "The card you pulled from the deck is " << *c << endl;
            cout << "----------------------------------------------" << endl;
            player->printOptions();
        }
};

int main() {
    Game* game = new Game(4);

    game->play();
    game->nextRound(game->players.front());

    //game->players.front()->printOptions();

    return 0;
}
