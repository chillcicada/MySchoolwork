from collections import defaultdict


class BranchedPolymer:
  def __init__(self):
    self.chains = {}  # chain_id → list of nodes
    self.chain_counter = 0  # current chain id
    self.node_map = defaultdict(list)  # node → list of chain_ids
    self.startpoints = set()  # nodes that are startpoints of any chain
    self.endpoints = set()  # nodes that are endpoints of any chain

  def _add_chain(self, nodes):
    if len(nodes) < 2:
      return -1

    chain_id = self.chain_counter
    self.chain_counter += 1
    self.chains[chain_id] = nodes.copy()

    for node in nodes:
      self.node_map[node].append(chain_id)

    # update start and end points
    self.startpoints.add(nodes[0])
    self.endpoints.add(nodes[-1])

    return chain_id

  def _remove_chain(self, chain_id):
    if chain_id not in self.chains:
      return

    nodes = self.chains[chain_id]
    # Remove from node_map
    for node in nodes:
      if chain_id in self.node_map[node]:
        self.node_map[node].remove(chain_id)
    # Check if start and end nodes are still endpoints in other chains
    start = nodes[0]
    if not any(self.chains[cid][0] == start or self.chains[cid][-1] == start for cid in self.node_map[start]):
      self.endpoints.discard(start)
    end = nodes[-1]

    if not any(self.chains[cid][0] == end or self.chains[cid][-1] == end for cid in self.node_map[end]):
      self.endpoints.discard(end)

    del self.chains[chain_id]

  def add_relation(self, a, b):
    a_exists = a in self.node_map
    b_exists = b in self.node_map

    if not a_exists and not b_exists:
      self._add_chain([a, b])
      return

    # Handle only one node exists
    existing_node, new_node = (a, b) if a_exists else (b, a)
    if not (a_exists ^ b_exists):  #
      return  # Both exist case not handled

    if existing_node in self.endpoints:
      handled = False
      for chain_id in self.node_map[existing_node][:]:  # Iterate copy
        if chain_id not in self.chains:
          continue
        chain = self.chains[chain_id]
        if chain[0] == existing_node:
          # Create new branch
          self._add_chain([existing_node, new_node])
          handled = True
          break
        elif chain[-1] == existing_node:
          # Extend this chain
          new_chain = chain + [new_node]
          self._remove_chain(chain_id)
          self._add_chain(new_chain)
          handled = True
          break
      if not handled:
        self._add_chain([existing_node, new_node])
    else:
      # Split existing chain containing middle node
      for chain_id in self.node_map[existing_node][:]:
        if chain_id not in self.chains:
          continue
        chain = self.chains[chain_id]
        if existing_node not in (chain[0], chain[-1]):
          pos = chain.index(existing_node)
          # Split into two parts
          part1 = chain[: pos + 1]
          part2 = chain[pos:]
          self._remove_chain(chain_id)
          self._add_chain(part1)
          self._add_chain(part2)
          # Add new relation chain
          self._add_chain([existing_node, new_node])
          break

  def get_all_chains(self):
    return list(self.chains.values())


if __name__ == '__main__':
  polymer = BranchedPolymer()
  polymer.from_topology('0-1,1-2,0-3,3-2,2-4')

  polymer.visualize()
  # 输出:
  # Branch 0: 0 -> 1 -> 2
  # Branch 1: 0 -> 3 -> 2
  # Branch 2: 2 -> 4
