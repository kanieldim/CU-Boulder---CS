# CSCI 3302: Homework 5 -- Clustering and Classification
# Implementations of K-Means clustering and K-Nearest Neighbor classification
import pickle
import random
import copy
import pdb
import matplotlib.pyplot as plt
import math
import numpy as np
from hw5_data import *

# TODO: INSERT YOUR NAME HERE
# Daniel Kim
LAST_NAME = "Kim"

################################################
# Base Code: No need to modify this part- it just plots your results
def visualize_data(data, cluster_centers_file):
  fig = plt.figure(1, figsize=(4,3))
  f = open(cluster_centers_file, 'rb')
  centers = pickle.load(f)
  f.close()

  km = KMeansClassifier()
  km._cluster_centers = centers

  colors = ['b', 'g', 'r', 'c', 'm', 'y', 'k']

  labels = []
  center_colors = []
  for pt in data:
    labels.append(colors[km.classify(pt) % len(colors)])

  for i in range(len(centers)):
    center_colors.append(colors[i])

  plt.scatter([d[0] for d in data], [d[1] for d in data], c=labels, marker='x')
  plt.scatter([c[0] for c in centers], [c[1] for c in centers], c=center_colors, marker='D')
  plt.title("K-Means Visualization")
  plt.show()

def print_and_save_cluster_centers(classifier, filename):
  for idx, center in enumerate(classifier._cluster_centers):
    print("  Cluster %d, center at: %s" % (idx, str(center)))


  f = open(filename,'wb')
  pickle.dump(classifier._cluster_centers, f)
  f.close()

def read_data_file(filename):
  f = open(filename)
  data_dict = pickle.load(f)
  f.close()

  return data_dict['data'], data_dict['labels']

def read_hw_data():
  global hw_data
  data_dict = pickle.loads(hw_data)
  return data_dict['data'], data_dict['labels']

def main():
  global LAST_NAME
  # read data file
  #data, labels = read_data_file('hw5_data.pkl')

  # load dataset
  data, labels = read_hw_data()

  # data is an 'N' x 'M' matrix, where N=number of examples and M=number of dimensions per example
  # data[0] retrieves the 0th example, a list with 'M' elements, one for each dimension (xy-points would have M=2)
  # labels is an 'N'-element list, where labels[0] is the label for the datapoint at data[0]


  ########## PART 1 ############
  # perform K-means clustering
  kMeans_classifier = KMeansClassifier()
  for datapoint in data:
    kMeans_classifier.add_datapoint(datapoint) # add data to the model

  kMeans_classifier.fit(4) # Fit 4 clusters to the data

  # plot results
  print('\n'*2)
  print("K-means Classifier Test")
  print('-'*40)
  print("Cluster center locations:")
  print_and_save_cluster_centers(kMeans_classifier, "hw5_kmeans_" + LAST_NAME + ".pkl")

  print('\n'*2)


  ########## PART 2 ############
  print("K-Nearest Neighbor Classifier Test")
  print('-'*40)

  # Create and test K-nearest neighbor classifier
  kNN_classifier = KNNClassifier()
  k = 4

  correct_classifications = 0
  # Perform leave-one-out cross validation (LOOCV) to evaluate KNN performance
  for holdout_idx in range(len(data)):
    # Reset classifier
    kNN_classifier.clear_data()

    for idx in range(len(data)):
      if idx == holdout_idx: continue # Skip held-out data point being classified

      # Add (data point, label) tuples to KNNClassifier
      kNN_classifier.add_labeled_datapoint(data[idx], labels[idx])

    guess = kNN_classifier.classify_datapoint(data[holdout_idx], k) # Perform kNN classification
    if guess == labels[holdout_idx]:
      correct_classifications += 1.0

  print("kNN classifier for k=%d" % k)
  print("Accuracy: %g" % (correct_classifications / len(data)))
  print('\n'*2)

  visualize_data(data, 'hw5_kmeans_' + LAST_NAME + '.pkl')

# Base Code: No need to modify
################################################

class KMeansClassifier(object):
  '''
  TODO: Implement a KMeans Classifier within this class by filling in code for each TODO
  '''
  def __init__(self):
    self._cluster_centers = [] # List of cluster centers, each of which is a point. ex: [ [10,10], [2,1], [0,-3] ]
    self._data = [] # List of datapoints (list of tuples, each of which is a point. ex:  [ (0,0) , (1.,5.), (2., 3.) ] )
    # Reminder: the difference between lists [] and tuples () are that lists can be modified, while tuples cannot.

  def add_datapoint(self, datapoint):
    self._data.append(datapoint)

  def fit(self, k):
    '''
    @param k: (int) Number of cluster centers to use in the algorithm
    '''
    # Fit k clusters to the data, by starting with k randomly selected cluster centers.
    self._cluster_centers = [] # Reset cluster centers array

    # TODO: Initialize k cluster centers at random points
    # HINT: To choose reasonable initial cluster centers, you can set them to be in the same spot as random (different) points from the datase
    #Using for loop, self._data[], and random.choice...

    for i in range(0, k):
        data = random.choice(self._data)
        self._cluster_centers.append(data)

    # TODO Follow convergence procedure to find final locations for each center
    while True:
      # TODO: Iterate through each datapoint in self._data and figure out which cluster it belongs to
      # HINT: Use self.classify(p) for each datapoint p to figure out which cluster it belongs to

      temp_cluster = []
      temp_cluster = list(self._cluster_centers)

      for i in range(0, len(temp_cluster)):
        temp_cluster[i] = [temp_cluster[i]]

      for j in self._data:
        temp_cluster[self.classify(j)].append(j)

      #print(temp)
      # TODO: Figure out new positions for each cluster center (should be the average of all of its points)
      # HINT: Store these new positions in a separate variable, so you can check how much they've changed for the next TODO

      new_positions_clusuter_center = [np.mean(new, axis = 0) for new in temp_cluster]

      # TODO: Check to see how much the cluster centers have moved (for the stopping condition)
      # HINT: np.linalg.norm( np.array(point1) - np.array(point2) ) will tell you the distance between two points

      total_sum = 0.0
      old_cluster_centers = []
      old_cluster_centers = self._cluster_centers

      for x in range(0, len(self._cluster_centers)):
        total_sum += np.linalg.norm( np.array(old_cluster_centers[x]) - np.array(new_positions_clusuter_center[x]))

      self._cluster_centers = list(new_positions_clusuter_center)

      # TODO: Check if the centers have moved less than some predefined threshold (some small value, e.g., 1e-5) then exit the loop
      # TODO: Add code to compute this value
      # if the sum is smaller than 1e-5, break
      if total_sum < 1e-5:
        break

    # TODO Set self._cluster_centers to contain each of the 'k' final cluster_centers

  def classify(self,p):
    '''
    @param p: Array representing a point
    @return closest_cluster_index: The index in self._cluster_centers corresponding to the closest cluster center to p
    '''
    # Given a data point p, figure out which cluster it belongs to and return that cluster's index (in the self._cluster_centers list)
    closest_cluster_index = 0

    # TODO Find nearest cluster center to point p, then return its index in self._cluster_centers
    # closet = min

    temp = []

    for count in self._cluster_centers:
        calculate = math.sqrt( sum( [ (nearest_cluster_center - point) ** 2 for nearest_cluster_center, point in zip(count, p) ] ) )
        temp.append(calculate)

    closest_cluster_index = temp.index( min(temp) )

    return closest_cluster_index

    # dist=[]
    # for c in self._cluster_centers:
    #   dist.append(math.sqrt(sum([(a-b)**2 for a, b in zip(c, p)])))
    # closest_cluster_index = dist.index(min(dist))
    # return closest_cluster_index


class KNNClassifier(object):
  '''
  TODO: Implement a K-nearest neighbor classifier in this class
  '''

  def __init__(self):
    self._data = [] # list of (datapoint, label) tuples

  def clear_data(self):
    # Removes all data stored within the model
    self._data = []

  def add_labeled_datapoint(self, data_point, label):
    '''
    @param data_point: Array of coordinates representing a point
    @param label: Value representing which class the data point belongs to
    '''
    # Adds a labeled datapoint tuple onto the object's _data member
    self._data.append((data_point, label))

  def classify_datapoint(self, data_point, k):
    '''
    @param data_point: Array of coordinates representing a point
    @param k: Integer indicating how many neighbors to take into account for the NN classification
    @return best_label: Value indicating the majority label from the neighbors considered
    '''
    label_counts = {} # Dictionary for you to use to map "label" => vote count
    best_label = None

    # Perform k_nearest_neighbor classification, setting best_label to the majority-vote label for k-nearest points
    #TODO: Find the k points closest to data_point in self._data
    #HINT: If you make a list of tuples mylist = [ (point1, distance1), (point2, distance2), ... ] and want to sort it, you can use mylist.sort(key=lambda x:x[1]) to sort by the second field of each tuple
    #Not using HINT

    label = [self._data[x][1] for x in range( len(self._data) )]
    data_list = np.array([self._data[y][0] for y in range( len(self._data) )])

    data_point = np.array(data_point)

    #Set up to find best_label
    temp = np.sum( (data_list - data_point) ** 2, 1 )
    index = np.argsort(temp)

    #TODO: Populate label_counts with the number of votes each label got from the k nearest points
    #TODO: Make sure to scale the weight of the vote each point gets by how far away it is from data_point (typically, further away = less weight)
    #      Since you're just taking the label with the most votes at the end of the algorithm, these do not need to be normalized in any way

    #Setting up number of votes
    for i in range(0, k):

      if label[index[i]] not in label_counts:
        label_counts[ label[index[i]] ] = 1

      else:
        label_counts[ label[index[i]] ] += 1

    #Temp_label list
    temp_label = [j for j in sorted( label_counts.keys() )]

    #Find max from final count
    final_count = [label_counts[k] for k in sorted(label_counts.keys())]
    final_count_max = max(final_count)

    #Matching index with max
    index = np.nonzero( np.array(final_count) == final_count_max)

    best_label = temp_label[index[0][0]]

    return best_label


if __name__ == '__main__':
  main()
