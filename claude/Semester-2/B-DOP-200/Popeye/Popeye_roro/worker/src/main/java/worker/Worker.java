package worker;

import redis.clients.jedis.Jedis;
import redis.clients.jedis.exceptions.JedisConnectionException;
import java.sql.*;
import org.json.JSONObject;

class Worker {
  public static void main(String[] args) {
    try {
        String redisHost = System.getenv("REDIS_HOST");
        if (redisHost == null) redisHost = "127.0.0.1";
        
        Jedis redis = connectToRedis(redisHost);
        Connection dbConn = connectToDB();

        System.err.println("Watching vote queue");

        while (true) {
            String voteJSON = redis.blpop(0, "votes").get(1);
            JSONObject voteData = new JSONObject(voteJSON);
            String voterID = voteData.getString("voter_id");
            String vote = voteData.getString("vote");

            System.err.printf("Processing vote for '%s' by '%s'\n", vote, voterID);
            updateVote(dbConn, voterID, vote);
        }
    } catch (SQLException e) {
      e.printStackTrace();
      System.exit(1);
    }
  }

  static void updateVote(Connection dbConn, String voterID, String vote) throws SQLException {
    PreparedStatement insert = dbConn.prepareStatement(
      "INSERT INTO votes (id, vote) VALUES (?, ?)");
    insert.setString(1, voterID);
    insert.setString(2, vote);

    try {
      insert.executeUpdate();
    } catch (SQLException e) {
      PreparedStatement update = dbConn.prepareStatement(
        "UPDATE votes SET vote = ? WHERE id = ?");
      update.setString(1, vote);
      update.setString(2, voterID);
      update.executeUpdate();
    }
  }

  static Jedis connectToRedis(String host) {
    Jedis conn = new Jedis(host);

    while (true) {
      try {
        conn.keys("*");
        break;
      } catch (JedisConnectionException e) {
        System.err.println("Waiting for redis");
        sleep(1000);
      }
    }

    System.err.println("Connected to redis");
    return conn;
  }

  static Connection connectToDB() throws SQLException {
    Connection conn = null;

    try {
      String host = System.getenv("POSTGRES_HOST");
      if (host == null) host = "127.0.0.1";
      
      String port = System.getenv("POSTGRES_PORT");
      if (port == null) port = "5432";
      
      String database = System.getenv("POSTGRES_DB");
      if (database == null) database = "postgres";
      
      String user = System.getenv("POSTGRES_USER");
      if (user == null) user = "postgres";
      
      String password = System.getenv("POSTGRES_PASSWORD");
      if (password == null) password = "password";

      Class.forName("org.postgresql.Driver");
      String url = "jdbc:postgresql://" + host + ":" + port + "/" + database;

      while (conn == null) {
        try {
            conn = DriverManager.getConnection(url, user, password);
        } catch (SQLException e) {
          System.err.println("Waiting for db");
          sleep(1000);
        }
      }

    } catch (ClassNotFoundException e) {
      e.printStackTrace();
      System.exit(1);
    }

    System.err.println("Connected to db");
    return conn;
  }

  static void sleep(long duration) {
    try {
      Thread.sleep(duration);
    } catch (InterruptedException e) {
      System.exit(1);
    }
  }
}
