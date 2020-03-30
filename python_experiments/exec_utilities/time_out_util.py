import shlex
import subprocess
from threading import Timer

import psutil


def kill_term_recursive(parent_pid):
    parent = psutil.Process(parent_pid)
    for child in parent.children(recursive=True):  # or parent.children() for recursive=False
        child.kill()
    parent.kill()


def run_with_timeout(cmd, timeout_sec, env=None):
    global is_time_out
    is_time_out = False
    if env is None:
        proc = subprocess.Popen(shlex.split(cmd), stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    else:
        proc = subprocess.Popen(shlex.split(cmd), stdout=subprocess.PIPE, stderr=subprocess.PIPE, env=env)

    def time_out_call_back(p):
        # print 'time out need to kill'
        global is_time_out
        is_time_out = True
        p.kill()

    timer = Timer(timeout_sec, time_out_call_back, [proc])
    try:
        timer.start()
        stdout, stderr = proc.communicate()
        # print str(stderr).replace('\n', '')
    finally:
        timer.cancel()
    # print is_time_out
    return is_time_out, str(stderr), str(stdout)


# not working...
# def kill_term_shell(pid):
#     kill_cmd = 'pkill -TERM -P {}'.format(pid)
#     print kill_cmd
#     print run_with_timeout(kill_cmd, timeout_sec=10)


if __name__ == '__main__':
    tle_flag, info_err, info = run_with_timeout('sleep 20', timeout_sec=5)
    # print tle_flag, info_err, info
