import glob
import math
import numpy as np
import pandas as pd
import scipy.stats as st
from numpy import sort
from matplotlib import pyplot as plt
import seaborn as sns
import statsmodels.api as sm


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

    return sort([sample_mean - r, sample_mean + r]), abs(r) * 2


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


def plot_confidence_interval(x_range, y_range, interval_width, color):
    for x, y, r in zip(x_range, y_range, interval_width):
        if r == 0:
            continue
        top = y + r
        bottom = y - r
        left = x - 2.5
        right = x + 2.5
        plt.plot([x, x], [top, bottom], color=color, linewidth=1)
        plt.plot([left, right], [top, top], color=color, linewidth=1)
        plt.plot([left, right], [bottom, bottom], color=color, linewidth=1)


def plot_calibration(palette, confidence):
    utilization_data = pd.read_csv('data/Scalar_Calibration_Lambda_Utilization.csv')

    X_range = [0, 230]
    Y_range = [-0.1, 1.1]
    T_range = ['120', '300']
    vFraction_range = ['0.25', '1']
    lambda_range = list(range(1, 100, 5))
    lambda_range.extend(list(range(100, 240, 20)))
    colors = iter(palette)

    utilization = []
    intervals = []
    for T in T_range:
        for vFraction in vFraction_range:
            for _lambda in lambda_range:
                config_data = utilization_data.query(
                    f"T == {T} and vFraction == {vFraction} and Lambda == {_lambda}").loc[:, 'value']
                utilization.append(config_data.aggregate('mean'))
                interval, r = confidence_interval(config_data, confidence)
                intervals.append(r)

            # plot lines
            color = next(colors)
            plt.plot(lambda_range, utilization,
                     marker=".", label=f'T={T}, vFraction={vFraction}', color=color, linestyle="dashed", linewidth=1)
            plot_confidence_interval(lambda_range, utilization, intervals, color)
            utilization = []
            intervals = []

    # plot items
    plt.title("System utilization over inter-arrival time")
    plt.xlabel("Mean inter-arrival time [s]")
    plt.ylabel("System utilization [%]")
    plt.legend(loc='upper right')
    # plt.grid(color='gray', linestyle='dotted')
    plt.xlim(X_range)
    plt.ylim(Y_range)
    plt.xticks(range(X_range[0], X_range[1] + 1, 20), labels=range(X_range[0], X_range[1] + 1, 20), rotation=45)
    plt.gcf().set_size_inches(19, 9.5)

    plt.savefig("calibration_utilization.svg", dpi=1200, format='svg')
    # plt.show()


def qq_plot(load, bulk, statistic):
    data = pd.read_csv(
        f'data/{statistic}/Factorial_Analysis_{load}_load_{"bulk" if bulk else "single"}_{statistic}.csv', sep=';',
        decimal=',')

    residuals = []

    for index, row in data.iterrows():
        d = row[5:] - row[5:].mean()
        residuals.extend(d)

    # sm.qqplot(np.array(residuals))
    # plt.savefig("qq.svg", dpi=1200, format='svg')
    # plt.close()

    residuals.sort()

    plt.grid(color='gray', linestyle='dotted')
    quantiles = np.array([((j + 1 - 0.5) / len(data) / 10, x) for j, x in enumerate(residuals)])
    normal_quantile = [st.norm.ppf(q) for q in quantiles[:, 0]]

    plt.plot(normal_quantile, residuals, linestyle='None', marker='.')
    z = np.polyfit(normal_quantile, residuals, 1)
    p = np.poly1d(z)
    plt.plot(normal_quantile, p(normal_quantile), "r--")
    labels = [
        "R{} = {:.3f}".format('\u00b2', np.corrcoef(normal_quantile, residuals)[0, 1] ** 2),
        f"Mean = {abs(np.mean(residuals)):.3f}",
        f"Std = {np.std(residuals, ddof=1):.3f}"
    ]

    plt.gca().annotate('\n'.join(labels),
                       xy=(0.01, 0.99), xycoords='axes fraction', fontsize='larger', verticalalignment='top')
    plt.title(f'{load.capitalize()} {"bulk" if bulk else "single"} {statistic}')
    plt.xlabel("Standard normal quantiles")
    plt.ylabel("Residuals quantiles")
    plt.savefig("qq1.svg", dpi=1200, format='svg')
    plt.show()


if __name__ == '__main__':
    # compute_validation_md1_confidence(confidence=0.95)
    # plot_calibration(sns.color_palette(), 0.99)
    qq_plot(load='low', bulk=False, statistic='utilization')
