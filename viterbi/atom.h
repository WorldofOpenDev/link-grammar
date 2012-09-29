/*************************************************************************/
/* Copyright (c) 2012                                                    */
/* Linas Vepstas <linasvepstas@gmail.com>                                */
/* All rights reserved                                                   */
/*                                                                       */
/*************************************************************************/

#ifndef _LG_VITERBI_ATOM_H
#define _LG_VITERBI_ATOM_H

#include <string>
#include <vector>

namespace link_grammar {
namespace viterbi {

// Classes generally resembling those of the OpenCog AtomSpace
// These are tailored for use for parsing.

/* TV: strength or likelihood of a link */
class TV
{
	public:
		float strength;
};

// Atom types.  Right now an enum, but maybe should be dynamic!?
enum AtomType
{
	WORD = 1,
	META,       // special-word, e.g. LEFT-WALL, RIGHT-WALL
	CONNECTOR,  // e.g. S+ 
	AND,
	OR,
	LINK,       // two connected connectors, e.g. Dmcn w/o direction info
	STATE
};


/* Base class for Nodes and Links */
/* Atoms are not mutable, except for the TV value. That is, you cannot
 * change the type of the atom.
 */
class Atom
{
	public:
		Atom(AtomType type) : _type(type) {}
		TV tv;
	protected:
		AtomType _type;
};

/* A Node may be 
 -- a word (the std::string holds the word)
 -- a link (the std::string holds the link)
 -- a disjunct (the std::string holds the disjunct)
 -- etc.
 * Nodes are immuatble; the name can be set but not changed.
 */
class Node : public Atom
{
	public:
		Node(AtomType t, const std::string& n)
			: Atom(t), _name(n) {}
	private:
		std::string _name;
};

/*
 * Links hold a bunch of atoms
 * Links are immutable; the outgoing set cannot be changed.
 */
class Link : public Atom
{
	public:
		Link(AtomType t, const std::vector<Atom*> oset)
			: Atom(t), _oset(oset) {}
	private:
		// Outgoing set
		std::vector<Atom*> _oset;
};


} // namespace viterbi
} // namespace link-grammar

#endif // _LG_VITERBI_ATOM_H