from collections import defaultdict


class Particle:
  def __init__(self, id_):
    self.id = id_
    pass

  def __repr__(self):
    return f'Particle({self.id})'


class BranchedPolymer:
  def __init__(self, root_=0):
    self.root = Particle(root_)
    self.nodes = {root_: self.root}
    self.branches = []
    self.endpoints = []
    self.node_to_branches = defaultdict(set)
    self._init_first_branch()
    pass

  def _init_first_branch(self):
    """创建初始分支（仅包含根节点）"""
    self.branches.append([self.root])
    self.endpoints.append(self.root)
    self.node_to_branches[self.root.id].add(0)

  def add_branch(self, from_node_id=None):
    """手动创建新分支。若指定 from_node_id，则以该节点为起点"""
    if from_node_id is None:
      from_node = self.root
    else:
      from_node = self.nodes.get(from_node_id)
      if not from_node:
        raise ValueError('指定的起点节点不存在')

    new_branch = [from_node]
    self.branches.append(new_branch)
    self.endpoints.append(from_node)
    new_branch_idx = len(self.branches) - 1
    self.node_to_branches[from_node.id].add(new_branch_idx)

  def add_node_to_branch(self, branch_idx, node_id: int):
    """向指定分支的末端添加节点，自动处理分支拆分"""
    if branch_idx >= len(self.branches):
      raise IndexError('分支索引超出范围')

    # 获取或创建节点
    if node_id in self.nodes:
      new_node = self.nodes[node_id]
    else:
      new_node = Particle(node_id)
      self.nodes[node_id] = new_node

    # 将节点添加到目标分支
    target_branch = self.branches[branch_idx]
    target_branch.append(new_node)
    self.endpoints[branch_idx] = new_node
    self.node_to_branches[new_node.id].add(branch_idx)

    # 检查是否需要拆分分支（该节点是否同时是其他分支的末端）
    existing_end_branches = [idx for idx, ep in enumerate(self.endpoints) if ep.id == new_node.id and idx != branch_idx]

    # 若该节点是其他分支的末端，则创建新分支
    if existing_end_branches:
      self.add_branch(from_node_id=new_node.id)

  def get_branches_by_node(self, node_id):
    """获取包含某节点的所有分支索引"""
    return list(self.node_to_branches.get(node_id, set()))

  def get_branch_nodes(self, branch_idx):
    """获取分支的节点列表"""
    return self.branches[branch_idx]

  def visualize(self):
    """简单可视化所有分支"""
    for i, branch in enumerate(self.branches):
      chain = ' -> '.join([str(node.id) for node in branch])
      print(f'Branch {i}: {chain}')

  def from_topology(self, topology):
    """根据拓扑字符串创建分支

    example:
      topology = '0-1,1-2,0-3,3-2,2-4'
      generate:
        Branch 0: 0 -> 1 -> 2
        Branch 1: 0 -> 3 -> 2
        Branch 2: 2 -> 4
    """
    # Clear existing data if any
    root_id = topology.split('-')[0]
    self.__init__(root_id)

    # Parse the topology string
    edges = set(topology.split(','))
    for edge in edges:
      start, end = map(int, edge.split('-'))

      # Create new branch if the start node is not in any branch
      if not self.get_branches_by_node(start):
        self.add_branch(from_node_id=start)

      # Add the end node to the branch
      branch_idx = self.get_branches_by_node(start)[0]
      self.add_node_to_branch(branch_idx, end)
    pass


if __name__ == '__main__':
  # # 初始化高分子链
  polymer = BranchedPolymer(0)
  # polymer.from_topology('0-1,1-2,0-3,3-2,2-4')

  # 向分支0添加节点
  polymer.add_node_to_branch(0, 1)
  polymer.add_node_to_branch(0, 2)  # 分支0: 0 -> 1 -> 2

  # 创建新分支并从根节点开始
  polymer.add_branch()  # 分支1: 0

  # 向分支1添加节点
  polymer.add_node_to_branch(1, 3)
  polymer.add_node_to_branch(1, 2)  # 分支1变为0 -> 3 -> 2，此时2已是分支0的末端，触发自动创建分支2

  # 向新生成的分支2添加节点
  polymer.add_node_to_branch(2, 4)  # 分支2: 2 -> 4

  # 查询节点2所在的分支
  print('节点2所在分支:', polymer.get_branches_by_node(2))  # 输出: [0, 1, 2]

  # 可视化所有分支
  polymer.visualize()
  # 输出:
  # Branch 0: 0 -> 1 -> 2
  # Branch 1: 0 -> 3 -> 2
  # Branch 2: 2 -> 4
