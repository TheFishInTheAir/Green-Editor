//
// Created by Ethan Breit on 2017-07-22.
//

#pragma once

#include <ge/console/enum/MessageType.h>
#include <string>

namespace ge
{
	namespace Log
	{
		void msg(std::string);
		void msg(std::string, std::string);

		void scc(std::string);
		void scc(std::string, std::string);


		void dbg(std::string);
		void dbg(std::string, std::string);

		void wrn(std::string);
		void wrn(std::string, std::string);

		void err(std::string);
		void err(std::string, std::string);

		void critErr(std::string);
		void critErr(std::string, std::string);

		void vrb(std::string);
		void vrb(std::string, std::string);

		void tVrb(std::string);
		void tVrb(std::string, std::string);


	}
}