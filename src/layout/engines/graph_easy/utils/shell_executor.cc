#include "layout/engines/graph_easy/utils/shell_executor.h"
#include "easy_graph/infra/status.h"
#include "easy_graph/infra/log.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <cstdlib>
#include <string>

EG_NS_BEGIN

Status ShellExecutor::execute(const std::string& script) {
	EG_DBG("%s", script);

	pid_t status = system(script.c_str());
	if (-1 == status)
	{
		EG_ERR("system execute return error!");
		return Status::FAILURE;
	}

	if (WIFEXITED(status) &&  (0 == WEXITSTATUS(status))) return Status::SUCCESS;

	EG_ERR("system execute {%s} exit status value = [0x%x], exit code: %d\n", script, status, WEXITSTATUS(status));
	return Status::FAILURE;
}

EG_NS_END
