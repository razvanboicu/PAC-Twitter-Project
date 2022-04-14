#include "Runtime.h"

Runtime::Runtime(char* IPAdress) :
	m_client()
{
	m_client.Initialize(IPAdress);
	m_handle = m_client.GetHandle();
	m_focus = std::make_unique<UserLogin>(m_handle);
}

void Runtime::Begin()
{
	while (m_focus->IsShowing())
	{
		m_focus->ShowWindow();
	}
	ChangeWindow(m_focus->getNextWindowEnum());
	Begin();
}

void Runtime::ChangeWindow(Windows window)
{
	int ID = 0;
	int oID = 0;
	int PostID = 0;
	std::string user;
	m_focus->m_window.close();
	switch (window)
	{
	case Windows::eLoginWindow:
		m_focus.release();
		m_focus.reset(new UserLogin(m_handle));
		break;
	case Windows::eRegisterWindow:
		m_focus.release();
		m_focus.reset(new RegisterWindow(m_handle));
		break;
	case Windows::eMainMenuWindow:
		if (dynamic_cast<UserLogin*>(m_focus.get()) != nullptr)
			m_username = dynamic_cast<UserLogin&>(*m_focus).GetUsername();
		m_focus.release();
		m_focus.reset(new MainMenuWindow(m_handle, m_username));
		if (dynamic_cast<MainMenuWindow*>(m_focus.get()) != nullptr)
			dynamic_cast<MainMenuWindow&>(*m_focus).SetUser(m_username);
		break;
	case Windows::ePostWindow:
		if (dynamic_cast<ProfileWindow*>(m_focus.get()) != nullptr)
		{

			if (dynamic_cast<ProfileWindow*>(m_focus.get())->WasRetweetPressed())
			{

				PostID = dynamic_cast<ProfileWindow*>(m_focus.get())->GetFocusedPostID();

			}
		}
		else if (dynamic_cast<OtherProfilesWindow*>(m_focus.get()) != nullptr)
		{
			if (dynamic_cast<OtherProfilesWindow*>(m_focus.get())->WasRetweetPressed())
				PostID = dynamic_cast<OtherProfilesWindow*>(m_focus.get())->GetFocusedPostID();
		}
		m_focus.release();
		m_focus.reset(new PostWindow(m_handle, PostID));
		dynamic_cast<PostWindow*>(m_focus.get())->setUsername(m_username);
		break;
	case Windows::eSearchKeywordWindow:
		user = dynamic_cast<MainMenuWindow*>(m_focus.get())->GetSearchBoxID();
		m_focus.release();
		m_focus.reset(new SearchKeywordWindow(m_handle,user,m_username));
		break;
	case Windows::eProfileWindow:
		if (dynamic_cast<SearchKeywordWindow*>(m_focus.get()) != nullptr)
		{
			ID = dynamic_cast<SearchKeywordWindow*>(m_focus.get())->GetPressedPostID();
		}
		if (dynamic_cast<OtherProfilesWindow*>(m_focus.get()) != nullptr)
		{
			ID = dynamic_cast<OtherProfilesWindow*>(m_focus.get())->GetRetweetedPostID();
		}
		if (dynamic_cast<FeedWindow*>(m_focus.get()) != nullptr)
		{
			ID = dynamic_cast<FeedWindow*>(m_focus.get())->GetPressedPostID();
		}
		m_focus.release();
		m_focus.reset(new ProfileWindow(m_handle,m_username,ID));;
		break;
	case Windows::eFeedWindow:
		m_focus.release();
		m_focus.reset(new FeedWindow(m_handle,m_username));
		break;
	case Windows::eOtherProfilesWindow:
		std::string friendUser;
		if (dynamic_cast<SearchKeywordWindow*>(m_focus.get()) != nullptr)
		{
			oID = dynamic_cast<SearchKeywordWindow*>(m_focus.get())->GetPressedPostID();
			friendUser = dynamic_cast<SearchKeywordWindow*>(m_focus.get())->GetPressedPostString();
		}
		if (dynamic_cast<MainMenuWindow*>(m_focus.get()) != nullptr) {
			friendUser = dynamic_cast<MainMenuWindow&>(*m_focus).GetFriendUser();
			user = dynamic_cast<MainMenuWindow&>(*m_focus).GetUser();
		}
		if (dynamic_cast<ProfileWindow*>(m_focus.get()) != nullptr)
		{
			oID = dynamic_cast<ProfileWindow*>(m_focus.get())->GetRetweetedPostID();
			friendUser = dynamic_cast<ProfileWindow*>(m_focus.get())->GetPostAuthor();
		}
		else if (dynamic_cast<OtherProfilesWindow*>(m_focus.get()) != nullptr)
		{
			oID = dynamic_cast<OtherProfilesWindow*>(m_focus.get())->GetRetweetedPostID();
			friendUser = dynamic_cast<OtherProfilesWindow*>(m_focus.get())->GetPostAuthor();

		}
		if (dynamic_cast<FeedWindow*>(m_focus.get()) != nullptr)
		{
			std::cout << "dadada";
			oID = dynamic_cast<FeedWindow*>(m_focus.get())->GetPressedPostID();
			friendUser = dynamic_cast<FeedWindow*>(m_focus.get())->GetPressedPostString();
		}
		m_focus.release();
		m_focus.reset(new OtherProfilesWindow(friendUser,m_username,m_handle,oID));
		break;
	}
}
