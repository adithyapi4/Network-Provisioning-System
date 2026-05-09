# AirConnect — Network Provisioning and Allotment System

A console-based C++ application that simulates the end-to-end mobile number provisioning workflow of a telecom operator. It models two roles — **Customer** and **Provisioner** — and walks each through the exact steps a real-world telecom service desk would follow: KYC collection, OTP verification, UPC validation, CRN generation, ICCID assignment, and final activation.

---

## Intent

The project demonstrates object-oriented design in C++ applied to a realistic domain. It shows how inheritance, friend functions, operator overloading, static class members, and exception handling can be combined to build a role-based interactive system. The telecom provisioning domain was chosen because it naturally maps to the concepts of encapsulation (customer data hidden behind a class), polymorphism (new connection vs. port-in handled by overloaded constructors), and state machines (Pending → Provisioned / Rejected).

---

## Features

### Customer Portal

| Feature | Details |
|---|---|
| New Connection | Collects name, pincode, Aadhaar number, and email; verifies email via OTP simulation |
| Port-In | All of the above plus the existing mobile number and UPC code; verifies mobile number via OTP |
| Connection Types | Prepaid (`PR`) and Postpaid (`PO`) — selectable for both New and Port-In flows |
| Email OTP Verification | Simulated on object construction via `Customer::verify_email()` |
| Mobile OTP Verification | Simulated for port-in requests via `Mobile::verify_no()` |

### UPC Validation (Port-In only)

The system identifies the current operator from the first character of the UPC code:

| Prefix | Operator |
|---|---|
| `V` | Vodafone Idea |
| `G` | Reliance Jio |
| `A` | Airtel |
| `B` | BSNL |
| `M` | MTNL |

One retry is allowed for an invalid UPC before the request is rejected with an exception.

### CRN Generation

Each request automatically receives a **Customer Reference Number (CRN)** composed of:

```
<type><connection_type><last-4-of-aadhaar><partial-pincode>
```

- `type`: `NE` (New Connection) or `PI` (Port-In)
- `connection_type`: `PR` (Prepaid) or `PO` (Postpaid)

The CRN is the primary key used by the provisioner to locate and activate a request.

### Provisioner Portal

| Feature | Details |
|---|---|
| Authentication | Provisioner ID + OTP verification before access |
| View Pending Requests | Lists all connections awaiting activation (shows CRN) |
| View Rejected Requests | Lists rejected requests with their rejection reason |
| View Provisioned Requests | Lists activated connections with their ICCID |
| Provision a Request | Select a CRN, assign an ICCID, and mark the connection as Provisioned |
| Mobile Number Assignment | For new connection requests, a new mobile number is algorithmically generated on provisioning |

---

## Project Structure

```
Network-Provisioning-System/
├── Customer.h      # Base class — KYC fields and email OTP
├── Customer.cpp    # Customer constructor and verify_email()
├── Mobile.h        # Derived class — connection-specific fields and friend declarations
├── Mobile.cpp      # Mobile constructors, CRN/mobile-no generation, UPC validation
└── main.cpp        # Entry point, menu loop, provisioner logic, operator<< overload
```

---

## Class Design

```
Customer  (base)
│  - name, pincode, aadhaar_no, email, status, otp
│  - verify_email()  [private]
│
└── Mobile  (derived)
       - type, connection_type, mobile_no, iccid, upc, crn, reason, status
       - static no_of_connections_requests
       - verify_no(), verify_upc(), generate_crn(), generate_mobile_no()
       - friend: mobile_provisioning(), operator<<
```

---

## Building and Running

**Requirements:** A C++17-compatible compiler (GCC 7+, Clang 5+, MSVC 2017+).

```bash
# Compile
g++ -std=c++17 Customer.cpp Mobile.cpp main.cpp -o airconnect

# Run
./airconnect
```

---

## Workflow Overview

```
[ Main Menu ]
    │
    ├─ 1. Customer
    │       ├─ Prepaid / Postpaid
    │       │       ├─ New Connection  →  KYC → Email OTP → CRN generated → "Pending"
    │       │       └─ Port In         →  KYC → Email OTP → Mobile OTP → UPC check → CRN → "Pending"
    │
    └─ 2. Provisioner
            │  Provisioner ID + OTP
            ├─ View Pending   →  Select CRN → Enter ICCID → "Provisioned"
            ├─ View Rejected
            └─ View Provisioned
```

---

## Notes

- OTP values are accepted from stdin without actual dispatch (simulation only).
- The `no_of_connections_requests` static counter tracks all requests across the session.
- The `goto` label in `verify_upc()` and `PROVISION_MENU` are intentional C-style flow constructs retained from the original implementation.
- In-memory storage only — data does not persist across runs.
