import uuid
from collections import defaultdict


class BranchedPolymer:
  def __init__(self):
    self.node_to_chain = defaultdict(set)
    self.chains = defaultdict(list)

    self.start_points = set()
    self.end_points = set()
    pass

  def add_branch(self, nodes):
    if len(nodes) < 2:
      return -1

    chain_id = uuid.uuid1()
    self.chains[chain_id] = nodes.copy()

    for node in nodes:
      self.node_to_chain[node].add(chain_id)

    self.start_points.add(nodes[0])
    self.end_points.add(nodes[-1])

    return chain_id

  def remove_branch(self, branch_id):
    if branch_id not in self.chains:
      return

    nodes = self.chains[branch_id]
    for node in nodes:
      if branch_id in self.node_to_chain[node]:
        self.node_to_chain[node].remove(branch_id)

    start = nodes[0]
    if not any(self.chains[cid][0] == start or self.chains[cid][-1] == start for cid in self.node_to_chain[start]):
      self.end_points.discard(start)

    end = nodes[-1]
    if not any(self.chains[cid][0] == end or self.chains[cid][-1] == end for cid in self.node_to_chain[end]):
      self.end_points.discard(end)

    del self.chains[branch_id]

  def append_node(self, branch_id, node):
    if branch_id not in self.chains:
      return

    chain = self.chains[branch_id]
    chain.append(node)
    self.chains[branch_id] = chain

    self.node_to_chain[node].add(branch_id)

    if chain[0] == node:
      self.start_points.add(node)

    if chain[-1] == node:
      self.end_points.add(node)
    return

  def add_node_pair(self, node1: int, node2: int):
    assert node1 != node2

    node1_exists = node1 in self.node_to_chain
    node2_exists = node2 in self.node_to_chain

    # case1: both nodes are new
    if not node1_exists and not node2_exists:
      self.add_branch([node1, node2])
      return

    # case2: both nodes are existing
    if node1_exists and node2_exists:
      pass

    # case3: one of the nodes is new
    existing_node, new_node = (node1, node2) if node1_exists else (node2, node1)

    #   subcase1: existing node is a start point
    if existing_node in self.start_points:
      self.add_branch([existing_node, new_node])
      return

    #   subcase2: existing node is an end point (and not a start point)
    if existing_node in self.end_points:
      return
    pass

  @classmethod
  def from_topology(cls, topology: str) -> 'BranchedPolymer':
    pass

  def visualize(self):
    pass
