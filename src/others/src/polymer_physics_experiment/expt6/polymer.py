from collections import defaultdict


class Polymer:
    def __init__(self):
        self.chains = {}  # chain_id → list of nodes
        self.chain_counter = 0
        self.node_map = defaultdict(list)  # node → list of chain_ids
        self.endpoints = set()  # nodes that are endpoints of any chain

    def _add_chain(self, nodes):
        if len(nodes) < 2:
            return -1  # invalid chain
        chain_id = self.chain_counter
        self.chain_counter += 1
        self.chains[chain_id] = nodes.copy()
        for node in nodes:
            self.node_map[node].append(chain_id)
        # Update endpoints
        self.endpoints.add(nodes[0])
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
        if not any(
            self.chains[cid][0] == start or self.chains[cid][-1] == start
            for cid in self.node_map[start]
        ):
            self.endpoints.discard(start)
        end = nodes[-1]
        if not any(
            self.chains[cid][0] == end or self.chains[cid][-1] == end
            for cid in self.node_map[end]
        ):
            self.endpoints.discard(end)
        del self.chains[chain_id]

    def is_endpoint(self, node):
        return node in self.endpoints

    def get_index_of_non_endpoint(self, node):
        if node not in self.node_map:
            return

        assert not self.is_endpoint(node)

        cids = self.node_map[node]

        assert len(cids) == 1

        chain = self.chains[cids[0]]

        for i, n in enumerate(chain):
            if n == node:
                return i, cids[0]

        return

    def is_only_chain_start(self, node):
        if node not in self.node_map:
            return False

        chains = [self.chains[cid] for cid in self.node_map[node] if cid in self.chains]
        return any(chain[0] == node and chain[-1] != node for chain in chains)

    def is_only_chain_end(self, node):
        if node not in self.node_map:
            return False

        chains = [self.chains[cid] for cid in self.node_map[node] if cid in self.chains]
        return any(chain[0] != node and chain[-1] == node for chain in chains)

    def add_relation(self, a, b):
        assert a != b

        a_exists = a in self.node_map
        b_exists = b in self.node_map

        if not a_exists and not b_exists:
            self._add_chain([a, b])
            return

        if a_exists and b_exists:
            # messy code
            if self.is_endpoint(a) and self.is_endpoint(b):
                if self.is_only_chain_start(a) and self.is_only_chain_start(b):
                    count_b = len(self.node_map[b])
                    if count_b == 1:
                        chain_b = self.chains[self.node_map[b][0]]
                        self._remove_chain(self.node_map[b][0])
                        self._add_chain([a] + chain_b)
                        return

                return

            if not self.is_endpoint(a) and self.is_endpoint(b):
                index_a, chain_id_a = self.get_index_of_non_endpoint(a)
                assert index_a is not None
                assert chain_id_a is not None

                chain_a = self.chains[chain_id_a].copy()

                if self.is_only_chain_start(b):
                    chain_b = self.chains[self.node_map[b][0]]

                    self._add_chain([a] + chain_b)
                    self._add_chain(chain_a[: index_a + 1])
                    self._add_chain(chain_a[index_a:])
                    self._remove_chain(chain_id_a)
                    self._remove_chain(self.node_map[b][0])
                    return
                return

            print(f'unhandled case: {a}, {b}')

            if self.is_endpoint(a) and not self.is_endpoint(b):
                return

            if not self.is_endpoint(a) and not self.is_endpoint(b):
                return

            return

        existing_node, new_node = (a, b) if a_exists else (b, a)

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

    def visualize(self):
        branches = sorted(self.chains.values(), key=lambda x: (x[0], x[-1]))
        for i, branch in enumerate(branches):
            chain = '-'.join([str(n) for n in branch])
            print(f'Branch {i + 1}: {chain}')
        return

    @classmethod
    def from_topology(cls, topology):
        p = cls()
        for edge in topology.split(','):
            a, b = map(int, edge.split('-'))
            p.add_relation(a, b)
        return p

    def export(self):
        return ','.join(
            f'{a}-{b}'
            for chain in self.chains.values()
            for a, b in zip(chain, chain[1:])
        )


p = Polymer().from_topology(
    '0-1,1-2,2-3,3-4,4-5,5-6,6-7,7-8,8-9,9-10,10-11,11-12,12-13,13-14,14-15,15-16,16-17,17-18,18-19,19-20,21-22,22-23,23-24,24-25,26-27,27-28,28-29,29-30,30-31,31-32,32-33,33-34,34-35,36-37,37-38,38-39,39-40,40-41,41-42,42-43,43-44,44-45,45-46,46-47,47-48,48-49,49-50,50-51,51-52,52-53,53-54,54-55,56-57,57-58,58-59,59-60,61-62,62-63,63-64,64-65,66-67,67-68,68-69,69-70,70-71,71-72,72-73,73-74,74-75,75-76,76-77,77-78,78-79,79-80,80-81,81-82,82-83,83-84,84-85,85-86,86-87,87-88,88-89,89-90,90-91,91-92,92-93,93-94,94-95,95-96,96-97,97-98,98-99,99-100,101-102,102-103,103-104,104-105,106-107,107-108,108-109,109-110,111-112,112-113,113-114,114-115,115-116,116-117,117-118,118-119,119-120,120-121,121-122,122-123,123-124,124-125,125-126,126-127,127-128,128-129,129-130,130-131,131-132,132-133,133-134,134-135,136-137,137-138,138-139,139-140,0-36,0-66,0-111,15-21,15-26,50-56,50-61,125-131,125-136,95-101,95-106'
)

p.visualize()
