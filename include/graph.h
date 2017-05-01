#ifndef ROS_MAP_GENERATOR_GRAPH_H
#define ROS_MAP_GENERATOR_GRAPH_H


#include <vector>
#include <unordered_map>

template <typename T>
class Graph {
 public:
  void add_edge(T v, T u);
  std::vector<T> neighbours(T &v);
  const std::vector<std::pair<T, T>> &edges();

 private:
  std::vector<std::pair<T, T>> edges_;
  std::unordered_map<T, std::vector<T>> adjacency_list_;
};

template <typename T>
const std::vector<std::pair<T, T>> &Graph<T>::edges() {
  return edges_;
}

template <typename T>
void Graph<T>::add_edge(T v, T u) {
  edges_.push_back({v, u});
  adjacency_list_[v].push_back(u);
}

template <typename T>
std::vector<T> Graph<T>::neighbours(T &v) {
  return adjacency_list_[v];
}


#endif //ROS_MAP_GENERATOR_GRAPH_H
