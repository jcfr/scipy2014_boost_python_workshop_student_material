#include <ctime>
#include <map>
#include <string>
#include <vector>

#include <boost/array.hpp>
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

typedef boost::array<Move, 2> Round;

Round make_round(Move m1, Move m2) {
    Round r;
    r[0] = m1;
    r[1] = m2;
    return r;
}

/* Compares m1 to m2.
   Returns -1 if m1 beats m2, 1 if m2 beats m1, and 0 for a tie.
 */
int score(Move m1, Move m2) {
    return scoreMap().find(m1)->second.find(m2)->second;
}

std::vector<int> score(const std::vector<Round>& rounds) {
    std::vector<int> rslt;
    BOOST_FOREACH(const Round& r, rounds) {
	rslt.push_back(score(r[0], r[1]));
    }
    return rslt;
}

class Player
{
public:
    Player(const std::string& name) : name_(name) {}

    virtual Move nextMove(const std::vector<Round>& history,
			  unsigned char my_pos) const = 0;

private:
    std::string name_;
};

std::vector<int> play(const Player& p1,
		      const Player& p2,
		      std::vector<int>::size_type rounds)
{
    std::vector<Round> history;
    history.reserve(rounds);
    for (std::vector<int>::size_type i = 0; i < rounds; ++i) {
	Move m1 = p1.nextMove(history, 0);
	Move m2 = p2.nextMove(history, 1);
	history.push_back(make_round(m1, m2));
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

    Move nextMove(const std::vector<Round>& history,
		  unsigned char my_pos) const
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
	if (history.empty())
	    return RandomMoveGenerator()();

	return (*history.rbegin())[(my_pos + 1) % 2];
    }
};

void test()
{
    TitForTat p1("t4t");
    Random p2("random");
    std::vector<int> results = play(p1, p2, 100);
    BOOST_FOREACH(int r, results) {
	std::cout << r << "\n";
    }
}
