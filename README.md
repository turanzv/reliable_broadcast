# Reliable Broadcast

Reliable broadcast example in C++. Currently implemented for the synchronous setting.

Ensures:
- Validity: All messages from an honest party are eventually received by honest nodes.
- Consistency: If an honest part delivers a message, then all honest parties deliver the same message.
- Totality: If an honest party delivers a message, then the message will be delivered by all honest parties.
- No Duplication: a message is delivered at most one time.
- No Creation: a delivered message must have been broadcast by a node.