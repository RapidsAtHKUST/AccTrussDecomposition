import os

if __name__ == '__main__':
    for file in ['time_breakdown.py', 'varying_parameters.py', 'opt_stage12_PP_SI.py', 'opt_stage3_IEP.py',
                 'opt_gpu.py', 'overall_end_to_end_time.py']:
        os.system('python {}/{}'.format('.', file))
