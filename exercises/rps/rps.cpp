#include <ctime>
#include <map>
#include <string>
#include <vector>

#include <boost/foreach.hpp>
#include <boost/random.hpp>

enum Move {
    Rock,
    Paper,
    Scissors
};

typedef std::map<Move, std::map<Move, int> > ScoreMap;
const ScoreMap& scoreMap() {
    static ScoreMap smap;
    static bool initialized = false;
    if (!initialized) {
	std::map<Move, int> rock;
	rock[Rock] = 0;
	rock[Paper] = 1;
	rock[Scissors] = -1;
	smap[Rock] = rock;

	std::map<Move, int> paper;
	paper[Rock] = -1;
	paper[Paper] = 0;
	paper[Scissors] = 1;
	smap[Paper] = paper;

	std::map<Move, int> scissors;
	scissors[Rock] = 1;
	scissors[Paper] = -1;
	scissors[Scissors] = 0;
	smap[Scissors] = scissors;

	initialized = true;
    }
    
    return smap;
}

struct Round
{
    Round(Move p1_move, Move p2_move) :
	p1(p1_move),
	p2(p2_move)
    {}

    Move p1, p2;
};

/* Compares m1 to m2.
   Returns -1 if m1 beats m2, 1 if m2 beats m1, and 0 for a tie.
 */
int score(Move m1, Move m2) {
    return scoreMap().find(m1)->second.find(m2)->second;
}

std::vector<int> score(const std::vector<Round>& rounds) {
    std::vector<int> rslt;
    BOOST_FOREACH(const Round& r, rounds) {
	rslt.push_back(score(r.p1, r.p2));
    }
    return rslt;
}

class Player
{
public:
    Player(const std::string& name) : name_(name) {}

    virtual Move nextMove(const std::vector<Round>& history,
			  unsigned char my_pos) const = 0;

    const std::string& name() const { return name_; }
    void setName(const std::string& n) { name_ = n; }

private:
    std::string name_;
};

std::vector<int> play(const Player& p1,
		      const Player& p2,
		      std::vector<int>::size_type num_rounds)
{
    std::vector<Round> history;
    history.reserve(num_rounds);
    for (std::vector<int>::size_type i = 0; i < num_rounds; ++i) {
	Move m1 = p1.nextMove(history, 0);
	Move m2 = p2.nextMove(history, 1);
	history.push_back(Round(m1, m2));
    }
    
    return score(history);
}

class RandomMoveGenerator
{
public:
    RandomMoveGenerator() : rng_(std::time(0)),
			    dist_(1, 3) 
    {}

    Move operator()() {
	switch (dist_(rng_)) {
	case 1:
	    return Rock;
	    break;

	case 2:
	    return Paper;
	    break;

	case 3:
	default:
	    return Scissors;
	    break;
	}	
    }

private:
    boost::random::mt19937 rng_;
    boost::random::uniform_int_distribution<> dist_;
};

class Random : public Player
{
public:
    Random(const std::string& name) : 
	Player(name)
    {}

    Move nextMove(const std::vector<Round>&,
		  unsigned char) const
    {
	return rmg_();
    }
    
private:
    mutable RandomMoveGenerator rmg_;
};

class TitForTat : public Player
{
public:
    TitForTat(const std::string& name) : 
	Player(name)
    {}

    Move nextMove(const std::vector<Round>& history,
		  unsigned char my_pos) const
    {
	assert(my_pos == 0 || my_pos == 1);

	if (history.empty())
	    return RandomMoveGenerator()();

	const Round& r = *history.rbegin();
	return (my_pos == 0) ? r.p2 : r.p1;
    }
};

std::string test()
{
    TitForTat p1("t4t");
    Random p2("random");
    std::vector<int> results = play(p1, p2, 100);

    std::vector<int>::size_type p1_wins, p2_wins;
    p1_wins = p2_wins = 0;

    BOOST_FOREACH(int r, results) {
	if (-1 == r)
	    ++p1_wins;
	else if (1 == r)
	    ++p2_wins;
	
	std::cout << r << "\n";
    }

    if (p1_wins > p2_wins)
	return "Player " + p1.name() + " wins!";
    else if (p2_wins > p1_wins)
	return "Player " + p2.name() + " wins!";
    else
	return "It was a tie!";
}
