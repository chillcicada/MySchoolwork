from collections import defaultdict, deque


class Node:
  def __init__(self, node_id):
    self.id = node_id

  def __eq__(self, other):
    return self.id == other.id

  def __hash__(self):
    return hash(self.id)

  def __repr__(self):
    return f'Node({self.id})'


class BranchedPolymer:
  def __init__(self, root_id='0'):
    self.root = Node(root_id)
    self.nodes = {root_id: self.root}
    self.branches = [[self.root]]  # 所有分支的节点列表
    self.endpoints = [self.root]  # 各分支的末端节点
    self.node_to_branches = defaultdict(set)
    self.node_to_branches[root_id].add(0)

  def get_branches_by_endpoint(self, node):
    """获取以指定节点为末端的分支索引"""
    return [idx for idx, ep in enumerate(self.endpoints) if ep == node]

  def add_branch(self, from_node=None):
    """手动创建新分支"""
    if from_node is None:
      from_node = self.root
    new_branch = [from_node]
    self.branches.append(new_branch)
    self.endpoints.append(from_node)
    new_idx = len(self.branches) - 1
    self.node_to_branches[from_node.id].add(new_idx)
    return new_idx

  def add_node_to_branch(self, branch_idx, node_id):
    """向指定分支末端添加节点（自动处理分支拆分）"""
    # 获取或创建节点
    if node_id in self.nodes:
      new_node = self.nodes[node_id]
    else:
      new_node = Node(node_id)
      self.nodes[node_id] = new_node

    # 添加到目标分支
    target_branch = self.branches[branch_idx]
    target_branch.append(new_node)
    self.endpoints[branch_idx] = new_node
    self.node_to_branches[new_node.id].add(branch_idx)

    # 检查是否需要拆分分支
    existing_ends = [idx for idx, ep in enumerate(self.endpoints) if ep == new_node and idx != branch_idx]
    if existing_ends:
      self.add_branch(from_node=new_node)

  @classmethod
  def from_topology(cls, topology_str):
    """从拓扑字符串创建高分子链"""
    # 解析拓扑结构
    edges = []
    node_set = set()
    for pair in topology_str.split(','):
      src, dst = pair.split('-')
      edges.append((src, dst))
      node_set.update([src, dst])

    # 构建邻接表和入度
    adj = defaultdict(list)
    in_degree = defaultdict(int)
    for src, dst in edges:
      adj[src].append(dst)
      in_degree[dst] += 1
      if src not in in_degree:
        in_degree[src] = 0

    # 确定根节点（入度为0）
    roots = [n for n, d in in_degree.items() if d == 0]
    if not roots:
      raise ValueError('Invalid topology: no root node')
    root_id = roots[0]

    # 拓扑排序
    polymer = cls(root_id=root_id)
    queue = deque([root_id])
    processed = set()

    while queue:
      current = queue.popleft()
      processed.add(current)

      for neighbor in adj.get(current, []):
        # 确保父节点已处理
        if current not in processed:
          continue

        # 获取父节点对象
        parent_node = polymer.nodes[current]

        # 查找可用的父端点分支
        end_branches = polymer.get_branches_by_endpoint(parent_node)

        if end_branches:
          # 使用第一个找到的分支
          target_branch = end_branches[0]
        else:
          # 如果是根节点则创建新分支
          if parent_node == polymer.root:
            target_branch = polymer.add_branch()
          else:
            raise ValueError(f'Cannot attach {neighbor} to {current} - parent not at branch end')

        # 添加子节点
        polymer.add_node_to_branch(target_branch, neighbor)

        # 更新队列
        if neighbor not in processed and all(p in processed for p in adj.get(neighbor, [])):
          queue.append(neighbor)

    return polymer

  def visualize(self):
    """可视化所有分支"""
    for i, branch in enumerate(self.branches):
      chain = '-'.join([str(n.id) for n in branch])
      print(f'Branch {i}: {chain}')


# 使用示例
if __name__ == '__main__':
  topology = '0-1,1-2,0-3,3-2,2-4'
  polymer = BranchedPolymer.from_topology(topology)
  polymer.visualize()
