# Endpoints

For the API, the various endpoints available are:

-   **[GET]**: `/api/v1/stats/` - This returns the **temperature**, **humidity**, **time**, **date** and the values of all the connected device that are not **deleted**. This will be requested occasionally by the end device but must `NEVER` be requested more than `TWICE` per `SECOND` or it will affect the performance of the system such as glitches on the screen.

-   **[GET]**: `/api/v1/ping/` - This endpoint is used by the client device to ping the server.

-   **[GET]**: `/api/v1/devices/` - This endpoint will return all the devices available in the system, excluding devices flagged as deleted.

-   **[GET]**: `/api/v1/devices/deleted/` - This endpoint will return all the devices flagged as deleted.

-   **POST**: `/api/v1/device/add/` - This endpoint is used to add a device to the system.

-   **POST**: `/api/v1/value/` - This endpoint is used to change the value of the appliance. **ON/OFF** for digital appliances or the **range value** for analog appliances

-   **POST**: `/api/v1/device/update/` - This endpoint is used to update the appliance. Changing the **name** or the connected **pin**.

-   **POST**: `/api/v1/device/delete/` - This endpoint is used to **flag** an appliance as deleted.

---

## NOTE

-   All endpoints should have a terminating forward slash `/`.

-   **[GET]**: `/api/v1/stats/` - This endpoint will be requested occasionally by the end device but must `NEVER` be requested more than `TWICE` per `SECOND` or it will affect the performance of the system such as glitches on the screen.
