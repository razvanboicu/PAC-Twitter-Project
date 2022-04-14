#include "Comment.h"

void Comment::SetAuthor(Profile author)
{
    //aici eventual apelam la getteri din Profile ca sa afisam aasa un preview de imagine al autorului comentariului
    m_author = author;
}

void Comment::SetComment(const std::string& comment)
{
    //cumva ar trb facut din PARTEA GRAFICA ca textul adaugat sa fie de tip string si sa fie pasat la parametrul din functie care apoi sa actualizeze comentariul
    m_comment = comment;
}

Comment& Comment::operator+()
{
    //in momementul in care se apreciaza un comentariu, functia asta o sa fie conectata la buton si ea face ++ la like-uri a comentariului
    m_likes++;
    return *this;
}

void Comment::SetHasReplies(const bool& yesOrNo) 
{// daca e Yes, inseamna ca avem reply-uri la acel comment si trb sa faceti grafic cumva afisarea numarului de reply-uri subtil intr-un colt sau cv
   // https ://imgur.com/a/4EsL2kN asemator cum avem la FACEBOOK
    m_hasReplies = yesOrNo; 
}
