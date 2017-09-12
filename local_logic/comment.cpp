#include "comment.h"
#include<string>
#include<vector>
#include<time.h>
#include<algorithm>
#include"id.h"
#include "RestaurantSystem.h"
using namespace COMMENT;

COMMENT::Comment::Comment(AccountID _customerId, const int _star,
	const string& _text /*= ""*/, CommentListId _commentListId /*= Nodata*/) :
	ID(), customerId(_customerId), text(_text), commentListId(_commentListId)
{
	if (_star < 0 || star>5)throw std::runtime_error("���ֲ��ԣ�");
	star = _star;
	time(&timeCreated);
}

COMMENT::Comment::Comment(AccountID _customerId, const int _star,
	const string& _text, CommentListId _commentListId, time_t _timeCreated):
	customerId(_customerId),star(_star),text(_text),
	commentListId(_commentListId),timeCreated(_timeCreated){}

const std::string& COMMENT::Comment::getText() const
{
	return text;
}

double COMMENT::Comment::getStar() const
{
	return star;
}

AccountID COMMENT::Comment::getCustomeId() const
{
	return AccountID();
}

CommentListId COMMENT::Comment::getCommentListId() const
{
	return commentListId;
}

void COMMENT::Comment::setText(const string& _text)
{
	text = _text;
}

time_t COMMENT::Comment::getTime() const
{
	return timeCreated;
}

void COMMENT::Comment::reTarget(CommentListId cli)
{
	commentListId = cli;
	RESTAURANT::Restaurant::CommentListMap.at(cli)->addComment(id());
}

void COMMENT::Comment::remove()
{
	RESTAURANT::Restaurant::CommentListMap.at(commentListId)->removeComment(id());
	commentListId = Nodata;
}

COMMENT::CommentList::CommentList(std::initializer_list<CommentId> il) :
	CommentIdList(il)
{

}

void COMMENT::CommentList::addComment(CommentId _commentId)
{
	CommentIdList.push_back(_commentId);
}

void COMMENT::CommentList::sortByTime(bool reverse /*= false*/)
{
	if (!reverse)
		n_sort([](const CommentId& lhs, const CommentId& rhs)->bool
	{return RESTAURANT::Restaurant::CommentMap.at(lhs)->getTime() < RESTAURANT::Restaurant::CommentMap.at(rhs)->getTime(); },reverse);
	else
		n_sort([](const CommentId& lhs, const CommentId& rhs)->bool
	{return RESTAURANT::Restaurant::CommentMap.at(lhs)->getTime() > RESTAURANT::Restaurant::CommentMap.at(rhs)->getTime(); }, reverse);
}

void COMMENT::CommentList::sortByStar(bool reverse /*= false*/)
{
	if (!reverse)
		n_sort([](const CommentId& lhs, const CommentId& rhs)->bool
	{return RESTAURANT::Restaurant::CommentMap.at(lhs)->getStar() < RESTAURANT::Restaurant::CommentMap.at(rhs)->getStar(); }, reverse);
	else
		n_sort([](const CommentId& lhs, const CommentId& rhs)->bool
	{return RESTAURANT::Restaurant::CommentMap.at(lhs)->getStar() > RESTAURANT::Restaurant::CommentMap.at(rhs)->getStar(); }, reverse);
}

void COMMENT::CommentList::removeComment(unsigned _commentId)
{
	for (auto it = CommentIdList.begin(); it != CommentIdList.end();)
	{
		if (*it == _commentId)
			it = CommentIdList.erase(it);
		else
			++it;
	}

}

double COMMENT::CommentList::star()
{
	double sum = 0.0;
	for (CommentId _id : CommentIdList)
		sum += RESTAURANT::Restaurant::CommentMap.at(_id)->getStar();
	return sum / CommentIdList.size();
}

std::vector<unsigned>::iterator COMMENT::CommentList::begin()
{
	return CommentIdList.begin();
}

std::vector<unsigned>::iterator COMMENT::CommentList::end()
{
	return CommentIdList.end();
}

std::vector<unsigned>::const_iterator COMMENT::CommentList::cbegin() const
{
	return CommentIdList.cbegin();
}

std::vector<unsigned>::const_iterator COMMENT::CommentList::cend() const
{
	return CommentIdList.cend();
}

void COMMENT::CommentList::n_sort(bool compareCommentId(const CommentId& lhs, const CommentId& rhs), bool reverse)
{
	std::sort(begin(), end(), compareCommentId);
}
