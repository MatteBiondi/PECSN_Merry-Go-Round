import math
import pandas as pd
import scipy.stats as st
from numpy import sort
from matplotlib import pyplot as plt


def compute_stats(data):
    # summation = 0
    # max_value = data[0]
    # min_value = data[0]

    # for value in data:
    #     summation += value
    #     max_value = max(max_value, value)
    #     min_value = min(min_value, value)

    # sample_mean = summation / float(len(data))

    # sample_var = 0
    # for value in data:
    #     sample_var += (value - sample_mean) ** 2

    # sample_var = sample_var / (len(data) - 1)
    # sample_std = math.sqrt(sample_var)

    # return min_value, max_value, summation, sample_mean, sample_var, sample_std
    return data.aggregate(['min', 'max', 'sum', 'mean', 'var', 'std']).to_dict()


def confidence_interval(data, level):
    stats = compute_stats(data)
    sample_std = stats['std']
    sample_mean = stats['mean']

    z_alpha = st.norm.ppf((1 - level) / 2, loc=0, scale=1)
    root_n = math.sqrt(len(data))
    r = (sample_std / root_n) * z_alpha

    return sort([sample_mean - r, sample_mean + r]), abs(r)*2


def compute_validation_md1_confidence(confidence):
    df = pd.read_csv('data/ValidationMD1.csv')

    print("Utilization")
    print("Lambda: 80\t",
          confidence_interval(df.query("Lambda == 80 and name.str.contains('Utilization')").loc[:, 'value'],
                              confidence))
    print("Lambda: 100\t",
          confidence_interval(df.query("Lambda == 100 and name.str.contains('Utilization')").loc[:, 'value'],
                              confidence))
    print("Lambda: 120\t",
          confidence_interval(df.query("Lambda == 120 and name.str.contains('Utilization')").loc[:, 'value'],
                              confidence))
    print("Throughput")
    print("Lambda: 80\t",
          confidence_interval(df.query("Lambda == 80 and name.str.contains('throughput')").loc[:, 'value'],
                              confidence))
    print("Lambda: 100\t",
          confidence_interval(df.query("Lambda == 100 and name.str.contains('throughput')").loc[:, 'value'],
                              confidence))
    print("Lambda: 120\t",
          confidence_interval(df.query("Lambda == 120 and name.str.contains('throughput')").loc[:, 'value'],
                              confidence))
    print("Queue Length")
    print("Lambda: 80\t",
          confidence_interval(df.query("Lambda == 80 and name.str.contains('queueLength')").loc[:, 'value'],
                              confidence))
    print("Lambda: 100\t",
          confidence_interval(df.query("Lambda == 100 and name.str.contains('queueLength')").loc[:, 'value'],
                              confidence))
    print("Lambda: 120\t",
          confidence_interval(df.query("Lambda == 120 and name.str.contains('queueLength')").loc[:, 'value'],
                              confidence))


def plot_calibration():
    utilization_data = pd.read_csv('data/Scalar_Calibration_Lambda_Utilization.csv')

    X_range = [0, 220]
    Y_range = [0, 1]
    T_range = ['120', '300']
    vFraction_range = ['0.25', '1']
    lambda_range = list(range(11, 100, 5))
    lambda_range.extend(list(range(100, 240, 20)))

    utilization = []
    for T in T_range:
        for vFraction in vFraction_range:
            for _lambda in lambda_range:
                utilization.append(
                    utilization_data
                    .query(f"T == {T} and vFraction == {vFraction} and Lambda == {_lambda}").loc[:, 'value']
                    .aggregate('mean'))
            plt.plot(lambda_range, utilization, marker='*', label=f'T={T}, vFraction={vFraction}')
            utilization = []

    plt.title("System utilization over inter-arrival time")
    plt.xlabel("Mean inter-arrival time [s]")
    plt.ylabel("System utilization [%]")
    plt.legend(loc='upper right')
    plt.grid(color='gray', linestyle='dotted')
    plt.xlim(X_range)
    plt.ylim(Y_range)
    plt.xticks(range(X_range[0], X_range[1] + 1, 10), labels=range(X_range[0], X_range[1] + 1, 10), rotation=45)
    plt.gcf().set_size_inches(19, 9.5)
    plt.savefig("calibration_utilization.svg", dpi=1200, format='svg')
    plt.show()


if __name__ == '__main__':
    compute_validation_md1_confidence(confidence=0.95)
    plot_calibration()
