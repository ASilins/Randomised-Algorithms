#ifndef TIMERUTILS_H
#define TIMERUTILS_H
#include <chrono>
#include <iostream>
#include <string>
#include <functional>

namespace TimerUtils {

    /**
     * Timing function that executes the passed function and returns the execution time with the result.
     *
     * @tparam return_value The type for the return value of the function
     * @tparam Func Type for the passed function
     * @tparam Args Type for the passed function arguments
     * @param func Function to be timed
     * @param args Arguments to be passed to the function
     * @return A tuple containing the time in microseconds and the returned value from the passed function
     */
    template <typename return_value, typename Func, typename... Args>
    std::tuple<uint64_t, return_value> time_experiment_with_result(Func &&func, Args &&...args) {
        const auto start = std::chrono::high_resolution_clock::now();

        auto func_result = std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);

        const auto end = std::chrono::high_resolution_clock::now();
        const auto time_result = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        return std::make_tuple(time_result, func_result);
    }

    /**
     * It uses `time_experiment_with_result` to time the passed function and print the message before executing it.
     *
     * @param message Message to print before executing the function
     */
    template<typename return_value, typename Func, typename... Args>
    std::tuple<uint64_t, return_value> time_experiment_with_result(const std::string& message, Func&& func, Args&&... args) {
        std::cout << message + "\n";
        return time_experiment_with_result<return_value>(std::forward<Func>(func), std::forward<Args>(args)...);
    }

    /**
     * A utility function to time a experiment execution time
     *
     * @tparam Func Type for the passed function
     * @tparam Args Type for the passed function arguments
     * @param func The function to be timed
     * @param args The arguments to be passed to the function
     * @return the time in microseconds it took to execute the method
     */
    template <typename Func, typename... Args>
    int64_t time_experiment(Func &&func, Args &&...args) {
        const auto start = std::chrono::high_resolution_clock::now();

        std::invoke(std::forward<Func>(func), std::forward<Args>(args)...);

        const auto end = std::chrono::high_resolution_clock::now();
        const auto time_result = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        return time_result;
    }

    /**
     * It uses `time_experiment` to time the passed function and print the message before executing it.
     */
    template <typename Func, typename... Args>
    uint64_t time_experiment(const std::string& message, Func&& func, Args&&... args) {
        std::cout << message + "\n";
        return time_experiment(std::forward<Func>(func), std::forward<Args>(args)...);
    }

    /**
     * A utility function to tima an experiment execution time and print the result time in console.
     *
     * @param message That will be printed with the result
     * @param func The function to be timed
     * @param args The arguments to be passed to the function
     */
    template <typename Func, typename... Args>
    void time_experiment_with_print(const std::string& message, Func&& func, Args&&... args) {
        std::cout << message + "\n";

        auto time = time_experiment(std::forward<Func>(func), std::forward<Args>(args)...);

        std::cout << message << " took: " << time << " microseconds" << std::endl;
    }
}

#endif //TIMERUTILS_H
