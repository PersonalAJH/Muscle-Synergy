/*	WARNING: COPYRIGHT (C) 2018 XSENS TECHNOLOGIES OR SUBSIDIARIES WORLDWIDE. ALL RIGHTS RESERVED.
	THIS FILE AND THE SOURCE CODE IT CONTAINS (AND/OR THE BINARY CODE FILES FOUND IN THE SAME
	FOLDER THAT CONTAINS THIS FILE) AND ALL RELATED SOFTWARE (COLLECTIVELY, "CODE") ARE SUBJECT
	TO A RESTRICTED LICENSE AGREEMENT ("AGREEMENT") BETWEEN XSENS AS LICENSOR AND THE AUTHORIZED
	LICENSEE UNDER THE AGREEMENT. THE CODE MUST BE USED SOLELY WITH XSENS PRODUCTS INCORPORATED
	INTO LICENSEE PRODUCTS IN ACCORDANCE WITH THE AGREEMENT. ANY USE, MODIFICATION, COPYING OR
	DISTRIBUTION OF THE CODE IS STRICTLY PROHIBITED UNLESS EXPRESSLY AUTHORIZED BY THE AGREEMENT.
	IF YOU ARE NOT AN AUTHORIZED USER OF THE CODE IN ACCORDANCE WITH THE AGREEMENT, YOU MUST STOP
	USING OR VIEWING THE CODE NOW, REMOVE ANY COPIES OF THE CODE FROM YOUR COMPUTER AND NOTIFY
	XSENS IMMEDIATELY BY EMAIL TO INFO@XSENS.COM. ANY COPIES OR DERIVATIVES OF THE CODE (IN WHOLE
	OR IN PART) IN SOURCE CODE FORM THAT ARE PERMITTED BY THE AGREEMENT MUST RETAIN THE ABOVE
	COPYRIGHT NOTICE AND THIS PARAGRAPH IN ITS ENTIRETY, AS REQUIRED BY THE AGREEMENT.
*/

#ifndef XSENS_THREADPOOL_H
#define XSENS_THREADPOOL_H

#include "xsens_mutex.h"

#include <map>
#include <set>
#include <deque>
#include <list>
#include <memory>

namespace xsens {

int processorCount();

class ThreadPoolTask {
public:
	virtual bool exec() = 0;				//!< \returns True if the task completed or false to reschedule the task
	virtual unsigned int needToWaitFor();
	ThreadPoolTask() {}
	virtual ~ThreadPoolTask() {}
	virtual void onError() {}				//!< Callback for when an error occurred during task execution. Any implementation of this function should NEVER throw an exception.
};

//lint -sem(xsens::ThreadPool::addTask, custodial(1))
class PooledTask;
class PooledThread;
class ThreadPool
{
public:
	typedef unsigned int TaskId;			//!< A type definition of a task ID

private:
	void reportTaskComplete(std::shared_ptr<PooledTask>);
	void reportTaskPaused(std::shared_ptr<PooledTask>);
	std::shared_ptr<PooledTask> getNextTask();
	friend class PooledThread;

	std::set<PooledThread*> m_threads;
	std::deque<std::shared_ptr<PooledTask>> m_tasks;
	std::map<TaskId, std::shared_ptr<PooledTask>> m_tasksSearch;
	std::map<TaskId, std::shared_ptr<PooledTask>> m_executing;
	std::map<TaskId, std::shared_ptr<PooledTask>> m_delaying;
	Mutex m_safe;
	TaskId m_nextId;
	bool m_suspended;

	std::shared_ptr<PooledTask> findTask(unsigned int id);

protected:
	ThreadPool();
	~ThreadPool();

public:
	TaskId addTask(ThreadPoolTask* task, TaskId afterId = 0);
	unsigned int count();
	void setPoolSize(unsigned int poolsize);
	unsigned int poolSize() const;
	bool doesTaskExist(TaskId id);
	void cancelTask(TaskId id, bool wait = true);
	void waitForCompletion(TaskId id);
	void suspend(bool wait = false);
	void resume();
	unsigned int executedCount(unsigned int thread) const;
	unsigned int completedCount(unsigned int thread) const;
	unsigned int failedCount(unsigned int thread) const;

	static ThreadPool* instance();
	static void destroy();
	static void setPool(ThreadPool* pool);
};

class TaskCompletionWaiter : public ThreadPoolTask
{
public:
	virtual bool exec();
	virtual unsigned int needToWaitFor();

	TaskCompletionWaiter(ThreadPool* pool = ThreadPool::instance());
	TaskCompletionWaiter(const std::list<unsigned int>& waitlist, ThreadPool* pool = ThreadPool::instance());
	virtual ~TaskCompletionWaiter();
	void addWaitId(unsigned int id);

private:
	ThreadPool* m_pool;
	std::list<unsigned int> m_waitList;
};

} // namespace xsens

#endif
