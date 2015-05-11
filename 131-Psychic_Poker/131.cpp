#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>

#define	 NUM_SUITS			4
#define  NUM_VALUES  		13

#define	 STRAIGHT_FLUSH		"straight-flush"
#define  FOUR_OF_A_KIND		"four-of-a-kind"
#define  FULL_HOUSE			"full-house"
#define	 FLUSH 				"flush"
#define  STRAIGHT 			"straight"
#define  THREE_OF_A_KIND	"three-of-a-kind"
#define  TWO_PAIRS		    "two-pairs"
#define  ONE_PAIR			"one-pair"
#define  HIGH_CARD			"highest-card"

class Card
{

public:

	Card(std::string cardStr);

	enum SUITS 	{CLUBS, HEARTS, DIAMONDS, SPADES};
	enum VALUES {ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING};

	int suit;
	int cardValue;

	std::string rawString;

	void setSuit(char suitVal);
	void setValue(char val);
};

typedef bool (*handEval)(std::vector<Card>, std::vector<std::vector<Card>>, std::vector<std::vector<Card>>);

Card::Card(std::string cardStr)
{
	setSuit(cardStr[1]);
	setValue(cardStr[0]);

	rawString = cardStr;
}

void Card::setSuit(char suitVal)
{
	if (suitVal == 'C')
		suit = CLUBS;
	else if (suitVal == 'H')
		suit = HEARTS;
	else if (suitVal == 'D')
		suit = DIAMONDS;
	else
		suit = SPADES;
}

void Card::setValue(char val)
{
	if (val == 'A')
		cardValue = ACE;
	else if (val >= '2' && val <= '9')
		cardValue = (val - '2') + TWO;
	else if (val == 'T')
		cardValue = TEN;
	else if (val == 'J')
		cardValue = JACK;
	else if (val == 'Q')
		cardValue = QUEEN;
	else
		cardValue = KING;
}

bool hasStraightFlush(std::vector<Card> cards, std::vector<std::vector<Card>> cardsBySuit, std::vector<std::vector<Card>> cardsByValue)
{
	for (int i=Card::ACE;i<=Card::TEN;i++)
	{
		bool matched = true;

		for (int j=0;j<5;j++)
		{
			if (cardsByValue[(i+j)%NUM_VALUES].size() == 0)
			{
				matched = false;
				break;
			}
		}

		if (matched == true)
		{			
			std::vector<int> suits(NUM_SUITS, 0);
			std::vector<int> updateSuits(NUM_SUITS, 0);

			for (int j=0;j<5;j++)
			{
				for(Card c: cardsByValue[(i+j)%NUM_VALUES])				
					updateSuits[c.suit]++;

				for (int k=0;k<NUM_SUITS;k++)
				{
					if (updateSuits[k] > 0)
						suits[k]++;

					updateSuits[k] = 0;
				}
			}

			for(int k=0;k<NUM_SUITS;k++)
			{
				if (suits[k] >= 5)
					return true;
			}
		}
	}

	return false;
}	

bool hasFourOfAKind(std::vector<Card> cards, std::vector<std::vector<Card>> cardsBySuit, std::vector<std::vector<Card>> cardsByValue)
{
	for(auto s : cardsByValue)
	{
		if (s.size() >= 4)
			return true;
	}

	return false;
}

bool hasFullHouse(std::vector<Card> cards, std::vector<std::vector<Card>> cardsBySuit, std::vector<std::vector<Card>> cardsByValue)
{
	int threeSets = 0;
	int twoSets = 0;

	for(auto s : cardsByValue)
	{
		if (s.size() == 2)
			twoSets++;
		else if (s.size() >= 3)
			threeSets++;
	}

	if ((twoSets >= 1 && threeSets >= 1) || threeSets >= 2)
		return true;
	else
		return false;
}

bool hasFlush(std::vector<Card> cards, std::vector<std::vector<Card>> cardsBySuit, std::vector<std::vector<Card>> cardsByValue)
{
	for(auto s : cardsBySuit)
	{
		if (s.size() >= 5)
			return true;
	}

	return false;
}

bool hasStraight(std::vector<Card> cards, std::vector<std::vector<Card>> cardsBySuit, std::vector<std::vector<Card>> cardsByValue)
{
	for (int i=Card::ACE;i<=Card::TEN;i++)
	{
		bool matched = true;

		for (int j=0;j<5;j++)
		{
			if (cardsByValue[(i+j)%NUM_VALUES].size() == 0)
			{
				matched = false;
				break;
			}
		}

		if (matched == true)
			return true;
	}

	return false;
}

bool hasThreeOfAKind(std::vector<Card> cards, std::vector<std::vector<Card>> cardsBySuit, std::vector<std::vector<Card>> cardsByValue)
{
	for (auto s : cardsByValue)
	{
		if (s.size() >= 3)
			return true;
	}

	return false;
}

int countPairs(std::vector<std::vector<Card>> cardsByValue)
{
	int count = 0;

	for (auto s: cardsByValue)
	{
		if (s.size() >= 2)
			count++;
	}

	return count;
}

bool hasTwoPair(std::vector<Card> cards, std::vector<std::vector<Card>> cardsBySuit, std::vector<std::vector<Card>> cardsByValue)
{
	int pairCount = countPairs(cardsByValue);

	return (pairCount >= 2);
}

bool hasOnePair(std::vector<Card> cards, std::vector<std::vector<Card>> cardsBySuit, std::vector<std::vector<Card>> cardsByValue)
{
	int pairCount = countPairs(cardsByValue);
	return (pairCount >= 1);
}

int evaluateHand(std::vector<Card> cards)
{	
	std::vector<handEval> evalFuncs {hasStraightFlush, hasFourOfAKind, hasFullHouse, hasFlush, hasStraight, hasThreeOfAKind, hasTwoPair, hasOnePair};
	std::vector<std::vector<Card>> 	cardsBySuit(NUM_SUITS, std::vector<Card>());
	std::vector<std::vector<Card>>	cardsByValue(NUM_VALUES, std::vector<Card>());	

	for(Card c: cards)
	{
		cardsBySuit[c.suit].push_back(c);
		cardsByValue[c.cardValue].push_back(c);		
	}

	for(int i=0;i<evalFuncs.size();i++)
	{
		if (evalFuncs[i](cards,cardsBySuit,cardsByValue) == true)
			return (evalFuncs.size()-i);
	}

	return 0;
}

void evalAndUpdate(std::vector<Card>& hand, int& bestHand)
{
	int handResult = evaluateHand(hand);
	bestHand = std::max(handResult, bestHand);
}

std::string computeBestHand(std::vector<Card> cards)
{
	std::vector<std::string> handResults {STRAIGHT_FLUSH, FOUR_OF_A_KIND, FULL_HOUSE, FLUSH, STRAIGHT, THREE_OF_A_KIND, TWO_PAIRS, ONE_PAIR, HIGH_CARD};
	
	int bestHand = 0; //HIGH_CARD	
	std::vector<Card> evalHand;
	
	//no discard
	evalHand.clear();
	evalHand.insert(evalHand.end(), cards.begin(), cards.begin()+5);
	evalAndUpdate(evalHand, bestHand);

	//discard 1
	for (int i=0;i<5;i++)
	{
		evalHand.clear();
		evalHand.insert(evalHand.end(), cards.begin(), cards.begin()+6);
		evalHand.erase(evalHand.begin()+i);		
		evalAndUpdate(evalHand, bestHand);
	}
	
	//discard 2
	for (int i=0;i<5;i++)
	{
		for (int j=i+1;j<5;j++)
		{
			evalHand.clear();
			evalHand.insert(evalHand.end(), cards.begin(), cards.begin()+7);
			evalHand.erase(evalHand.begin()+j);
			evalHand.erase(evalHand.begin()+i);
			evalAndUpdate(evalHand, bestHand);
		}
	}
	
	//discard 3
	for (int i=0;i<5;i++)
	{
		for (int j=i+1;j<5;j++)
		{
			evalHand.clear();
			evalHand.insert(evalHand.end(), cards.begin()+i, cards.begin()+i+1);
			evalHand.insert(evalHand.end(), cards.begin()+j, cards.begin()+j+1);			
			evalHand.insert(evalHand.end(), cards.begin()+5, cards.begin()+8);			
			evalAndUpdate(evalHand, bestHand);
		}
	}
	
	//discard 4
	for (int i=0;i<5;i++)
	{
		evalHand.clear();
		evalHand.insert(evalHand.end(), cards.begin()+i, cards.begin()+i+1);
		evalHand.insert(evalHand.end(), cards.begin()+5, cards.begin()+9);			
		evalAndUpdate(evalHand, bestHand);	
	}
	
	//discard 5
	evalHand.clear();
	evalHand.insert(evalHand.end(), cards.begin()+5, cards.begin()+10);
	evalAndUpdate(evalHand, bestHand);	

	return handResults[handResults.size()-bestHand-1];
}

int main(int argc, char** argv)
{
	int counter = 0;
	std::string cardIn;
	std::vector<Card> hand;

	while(std::cin >> cardIn)
	{
		hand.push_back(cardIn);
		counter++;

		if ((counter % 10) == 0)
		{
			std::cout << "Hand: ";

			for (int i=0;i<5;i++)
			{
				std::cout << hand[i].rawString << " ";
			}

			std::cout << "Deck: ";

			for (int i=5;i<hand.size();i++)
			{
				std::cout << hand[i].rawString << " ";
			}

			std::cout << "Best hand: ";

			std::cout << computeBestHand(hand) << "\n";
			hand.clear();			
		}
	}	
}